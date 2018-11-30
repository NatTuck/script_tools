defmodule Mix.Tasks.Compile.SimpleMake do
  def run(_args) do
    {output, 0} = System.cmd("make", [])
    IO.binwrite(output)
  end
end
