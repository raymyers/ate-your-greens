# Ate Your Greens

Unofficial syntax for [EYG lang](https://github.com/CrowdHailer/eyg-lang) and verifier for the pure subset.

EYG means Eat Your Greens, a metaphor for choices with long-term benefit.

AYG = Ate Your Greens, or Applicative EYG. "Ate" in the past tense means to imply exploration of what some of EYG's long-term benefits could be. 

## Syntax

EYG lang does not define a syntax, only an Intermediate Represenation (IR). Here is the unofficial syntax this repo defines: 

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

More examples in `examples` folder. There are some decisions made to make it easier to generate parsers for many languages. For instance:

* Semi-colons after `let` are not mandatory

## Status

* Define syntax and parser for EYG - DONE
* Transform AST to IR - Soon
* Enable verification on pure IR subset - Soon-ish

The parser is generated with [BNFC](https://github.com/BNFC/bnfc), which creates compiler front-ends for multiple languages.

* Haskell (Tested)
* Java
* C
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

``
cd generated/haskell
make
```

## Run

./generated/haskell/Eyg/Test examples/example1.eyg 

./generated/haskell/Eyg/Test examples/example-all.eyg 

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
