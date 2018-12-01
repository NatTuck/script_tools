# ScriptTools

Writing standard CLI scripts doesn't quite work in Elixir because standard *nix
operations (like "system") aren't exposed.

This library exposes some of that functionality.

These functions may not be suitable for use in a long-running application due to
not leaving the BEAM process in a consistent state or even still running.

Functionality:

 - system (3)
 - fork (2)
 - execvp (2)
 - exit (3)

## Installation

```elixir
def deps do
  [
    {:script_tools, "~> 0.1", git: "https://github.com/NatTuck/script_tools" }
  ]
end
```

## Future

If [available in Hex](https://hex.pm/docs/publish), the package can be installed
by adding `script_tools` to your list of dependencies in `mix.exs`:

Documentation can be generated with [ExDoc](https://github.com/elixir-lang/ex_doc)
and published on [HexDocs](https://hexdocs.pm). Once published, the docs can
be found at [https://hexdocs.pm/script_tools](https://hexdocs.pm/script_tools).

## Copyright

Copyright 2018 Nat Tuck

This library is licensed under the Apache License, Version 2.0. The license is
included, or a copy may be found at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, this software is
distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
either express or implied.

