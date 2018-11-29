defmodule ScriptToolsTest do
  use ExUnit.Case
  doctest ScriptTools

  test "greets the world" do
    assert ScriptTools.hello() == :world
  end
end
