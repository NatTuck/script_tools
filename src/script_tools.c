
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <alloca.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

#include <erl_nif.h>

static
ERL_NIF_TERM
make_ok(ErlNifEnv* env, ERL_NIF_TERM val)
{
    ERL_NIF_TERM ok = enif_make_atom(env, "ok");
    return enif_make_tuple(env, 2, ok, val);
}

static
ERL_NIF_TERM
make_error(ErlNifEnv* env, const char* emsg)
{
    ERL_NIF_TERM err = enif_make_atom(env, "error");
    ERL_NIF_TERM msg = enif_make_atom(env, emsg);
    return enif_make_tuple(env, 2, err, msg);
}

static
ERL_NIF_TERM
make_error_int(ErlNifEnv* env, const char* emsg, int code)
{
    ERL_NIF_TERM err = enif_make_atom(env, "error");
    ERL_NIF_TERM msg = enif_make_atom(env, emsg);
    ERL_NIF_TERM num = enif_make_int(env, code);
    ERL_NIF_TERM bod = enif_make_tuple(env, 2, msg, num);
    return enif_make_tuple(env, 2, err, bod);
}

static
ERL_NIF_TERM
st_exit(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    assert(argc == 1);

    int code;
    int rv = enif_get_int(env, argv[0], &code);
    if (!rv) {
        return make_error(env, "badarg");
    }

    // iex puts us in some weird input mode, let's reset that
    system("stty sane");

    exit(code);

    // can't get here
    return enif_make_int(env, -1);
}

static
ERL_NIF_TERM
make_wait_ret(ErlNifEnv *env, int rv)
{
    if (rv == -1) {
        return make_error(env, "nochild");
    }

    if (WIFEXITED(rv)) {
        int code = WEXITSTATUS(rv);
        if (code == 0) {
            return enif_make_atom(env, "ok");
        }
        else {
            return make_error_int(env, "exit", code);
        }
    }
    else if (WIFSIGNALED(rv)) {
        return make_error_int(env, "signal", WTERMSIG(rv));
    }
    else {
        return make_error(env, "unknown");
    }
}

static
ERL_NIF_TERM
st_system(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    assert(argc == 1);

    ErlNifBinary cmd;
    int rv = enif_inspect_binary(env, argv[0], &cmd);
    if (!rv) {
        return make_error(env, "badarg");
    }

    // iex puts us in some weird input mode, save it and reset it
    struct termios term_state;
    tcgetattr(0, &term_state);
    system("stty sane");

    rv = system(strndupa(cmd.data, cmd.size));

    // restore whatever weird terminal state we started in
    tcsetattr(0, TCSANOW, &term_state);

    return make_wait_ret(env, rv);
}

static
ERL_NIF_TERM
st_execvp(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    assert(argc == 2);
    int rv;

    ErlNifBinary text;
    rv = enif_inspect_binary(env, argv[0], &text);
    if (!rv) {
        return make_error(env, "badarg");
    }
    char* cmd = strndupa(text.data, text.size);

    unsigned int size;
    rv = enif_get_list_length(env, argv[1], &size);
    if (!rv) {
        return make_error(env, "badarg");
    }

    char** args = alloca(size * sizeof(char*));

    ERL_NIF_TERM head;
    ERL_NIF_TERM tail = argv[1];

    for (unsigned int ii = 0; ii < size; ++ii) {
        rv = enif_get_list_cell(env, tail, &head, &tail);
        if (!rv) {
            return make_error_int(env, "badarg", ii);
        }

        rv = enif_inspect_binary(env, head, &text);
        if (!rv) {
            return make_error_int(env, "badarg", ii);
        }

        args[ii] = strndupa(text.data, text.size);
    }

    // Make sure we don't stay stuck in awkward terminal mode.
    system("stty sane");

    rv = execvp(cmd, args);
    assert(rv == -1);
    return make_error_int(env, "errno", errno);
}

static
ERL_NIF_TERM
st_fork(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    assert(argc == 0);
    int rv = fork();
    if (rv == -1) {
        return make_error(env, "failed");
    }
    return make_ok(env, enif_make_int(env, rv));
}

static
ERL_NIF_TERM
st_waitpid(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    assert(argc == 1);

    int pid;
    int rv = enif_get_int(env, argv[0], &pid);
    if (!rv) {
        return make_error(env, "badarg");
    }

    int status;
    rv = waitpid(pid, &status, 0);
    if (!rv) {
        return make_error(env, "wait");
    }

    return make_wait_ret(env, status);
}

static ErlNifFunc funcs[] =
{
    {"sys_exit", 1, st_exit, 0},
    {"system", 1, st_system, ERL_NIF_DIRTY_JOB_IO_BOUND},
    {"execvp", 2, st_execvp, 0},
    {"fork", 0, st_fork, 0},
    {"waitpid", 1, st_waitpid, ERL_NIF_DIRTY_JOB_IO_BOUND},
};

ERL_NIF_INIT(Elixir.ScriptTools, funcs, NULL, NULL, NULL, NULL)

