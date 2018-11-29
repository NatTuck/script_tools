defmodule ScriptTools do
  @moduledoc """
  ScriptTools - Some tools for scripts.
  """

  @on_load :load_native
  def load_native do
    :erlang.load_nif('./tools', 0)
  end

  @doc """
  Exit the entire system process.
  """
  def sys_exit(code) do
    raise "NIF didn't happen for exit(#{code})"
  end

  def sys_exit do
    sys_exit(0)
  end
end
