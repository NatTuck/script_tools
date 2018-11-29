#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>

#include <erl_nif.h>

static
ERL_NIF_TERM
st_exit(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    int code;
    enif_get_int(env, argv[0], &code);

    // Get us back to canonical input mode.
    system("stty sane");

    exit(code);

    // can't get here
    return enif_make_int(env, -1);
}

static
ERL_NIF_TERM
st_system(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{

}

static ErlNifFunc funcs[] =
{
    {"sys_exit", 1, st_exit}
};

ERL_NIF_INIT(Elixir.ScriptTools, funcs, NULL, NULL, NULL, NULL)

