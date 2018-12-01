defmodule ScriptTools do
  @moduledoc """
  ScriptTools - Some tools for scripts.
  """

  @on_load :load_native
  def load_native do
    priv = :code.priv_dir(:script_tools)
    if File.exists?(priv) do
      :erlang.load_nif(priv ++ '/script_tools', 0)
    else
      :ok
    end
  end

  @doc """
  Exit the VM's system process.

  This gives the running VM no chance to clean up anything.
  """
  def sys_exit(code) do
    raise "NIF didn't happen for exit(#{code})"
  end

  def sys_exit do
    sys_exit(0)
  end

  @doc """
  Run a command in the foreground, block until it completes.

  The terminal is reset before running the new program, and is restored
  before resuming the VM.
  """
  def system(cmd) do
    raise "NIF didn't happen for system(#{cmd})"
  end

  @doc """
  Replace our VM with a newly executed program.

  This gives the running VM no chance to clean up anything.

  The terminal is reset before running the new program.
  """
  def execvp(cmd, _args) do
    raise "NIF didn't happen for execvp(#{cmd}, ...)"
  end

  @doc """
  Duplicate the current system process. See "man 2 fork" for details.

  This is almost certainly a bad idea. It only copies the active thread, so
  things will probably go horribly wrong if the VM tries to do *anything*.
  """
  def fork() do
    raise "NIF didn't happen for fork()"
  end

  @doc """
  Waits for a child process by pid.

  This is probably not useful.
  """
  def waitpid(pid) do
    raise "NIF didn't happen for waitpid(#{pid})"
  end
end
