defmodule ScriptTools do
  @moduledoc """
  ScriptTools - Some tools for scripts.
  """

  @on_load :load_native
  def load_native do
    :erlang.load_nif('./tools', 0)
  end

  @doc """
  Exit the VM's system process.
  """
  def sys_exit(code) do
    raise "NIF didn't happen for exit(#{code})"
  end

  def sys_exit do
    sys_exit(0)
  end

  @doc """
  Run a command in the foreground, block until it completes.
  """
  def system(cmd) do
    raise "NIF didn't happen for system(#{cmd})"
  end

  @doc """
  Replace our VM with a newly executed program.
  """
  def execvp(cmd, _args) do
    raise "NIF didn't happen for execvp(#{cmd}, ...)"
  end

  @doc """
  Duplicate the current system process. See "man 2 fork" for details.

  This is a bad idea.
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
