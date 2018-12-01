defmodule Mix.Tasks.Compile.SimpleMake do
  def run(_args) do
    {output, code} = System.cmd("make", [])
    if code == 0 do
      unless output =~ ~r/up to date/ do
        IO.binwrite(output)
      end
      :ok
    else
      IO.binwrite(output)
      {:error, "compile error"}
    end
  end
end
