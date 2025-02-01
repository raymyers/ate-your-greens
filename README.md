# Ate Your Greens

Unofficial syntax for [EYG lang](https://github.com/CrowdHailer/eyg-lang) and (eventually) verifier for the pure subset.

EYG = Eat Your Greens, a metaphor for choices with long-term benefit. It's a small language being created by Peter Saxton with interesting properties.

AYG = *Ate* Your Greens. It's an exploration of what some of EYG's long-term benefits could be. The focus on pure code (no side-effects) gives us a useful subset to start with for prototyping compilation and Formal Verification.

## Status

* Define syntax and parser for EYG - DONE
* Transform AST to IR - Soon
* Enable verification on IR pure subset - Soon-ish

## Syntax

EYG lang does not define a syntax, only an Intermediate Represenation (IR). This repo defines the following syntax over EYG: 

```rust
let script = |closure| {
    let js = !to_javascript(closure, {});
    !string_append("<script>", !string_append(js, "</script>"))
};
let name = match perform Prompt("What is your name?") {
    case Ok (value) -> value
    case Error (_) -> "Alice"
};
let client = |_| {
    let message = !string_append("Hello, ", name);
    let _ = perform Alert(message);
    {}
};
let page = script(client);
let page = !string_to_binary(page);

perform Download({name: "index.html", content: page})
```

The AYG subset would disallow the `perform` keyword.

More examples in `examples` folder. There are some decisions made to make it easier to generate parsers for many languages. For instance:

* Semi-colons after `let` are not mandatory

## Targets

The parser is generated with [BNFC](https://github.com/BNFC/bnfc), which creates compiler front-ends for multiple languages.

* Haskell (Tested)
* Java
* C (Tested)
* C++
* OCaml

BNFC also produces highlighter support with tree-sitter and pygments.

## Setup

* Haskell
* [just](https://just.systems/) command runner (optional)

To regenerate Haskell front-end

* BNFC
* Happy
* Alex

Explanation of dependencies TBD.

## Build

```
cd generated/haskell
make
```

## Run

This will run the parser and show diagostic output.

```
./generated/haskell/Eyg/Test examples/example1.eyg 

./generated/haskell/Eyg/Test examples/example-all.eyg
```

## Generate parser

```
just build-haskell
```

Which is short for:

```
bnfc -d -m grammar/Eyg.cf -o generated/haskell/
cd generated/haskell
make
```
