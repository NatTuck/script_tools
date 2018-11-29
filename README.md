# ScriptTools

Writing standard CLI scripts doesn't quite work in Elixir because standard *nix
operations (like "system") aren't exposed.

This library exposes some of that functionality.

These functions may not be suitable for use in a long-running application due to
not leaving the BEAM process in a consistent state or even still running.

## Installation

If [available in Hex](https://hex.pm/docs/publish), the package can be installed
by adding `script_tools` to your list of dependencies in `mix.exs`:

```elixir
def deps do
  [
    {:script_tools, "~> 0.1.0"}
  ]
end
```

Documentation can be generated with [ExDoc](https://github.com/elixir-lang/ex_doc)
and published on [HexDocs](https://hexdocs.pm). Once published, the docs can
be found at [https://hexdocs.pm/script_tools](https://hexdocs.pm/script_tools).

