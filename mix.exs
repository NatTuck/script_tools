defmodule ScriptTools.MixProject do
  use Mix.Project

  def project do
    # Might make more sense to put this compiler task
    # outside lib and manually load it here?
    #Code.require_file("lib/mix/tasks/compile.simple_make.ex")
    [
      app: :script_tools,
      version: "0.1.0",
      elixir: "~> 1.7",
      start_permanent: Mix.env() == :prod,
      deps: deps(),
      compilers: Mix.compilers ++ [:simple_make],
      #compilers: [:simple_make | Mix.compilers],
    ]
  end

  # Run "mix help compile.app" to learn about applications.
  def application do
    [
      extra_applications: [:logger]
    ]
  end

  # Run "mix help deps" to learn about dependencies.
  defp deps do
    [
      # {:dep_from_hexpm, "~> 0.3.0"},
      # {:dep_from_git, git: "https://github.com/elixir-lang/my_dep.git", tag: "0.1.0"},
    ]
  end
end
