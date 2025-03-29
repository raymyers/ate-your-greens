# Ate Your Greens

Unofficial syntax for [EYG lang](https://github.com/CrowdHailer/eyg-lang) and (eventually) verifier for the pure subset.

EYG = Eat Your Greens, a metaphor for choices with long-term benefit. It's a small language being created by Peter Saxton with interesting properties.

AYG = *Ate* Your Greens. It's an exploration of what some of EYG's long-term benefits could be. The focus on pure code (no side-effects) gives us a useful subset to start with for prototyping compilation and Formal Verification.

## Status

* Define syntax and parser for EYG - DONE
* Transform AST to IR - Soon
* Enable verification on IR pure subset - later

## Syntax

EYG lang does not define a syntax, only an Intermediate Representation (IR). This repo defines the following syntax over EYG: 

```rust
script = |closure| {
    js = !to_javascript(closure, {})
    !string_append("<script>", !string_append(js, "</script>"))
}
name = match perform Prompt("What is your name?") {
    Ok (value) -> value
    Error (_) -> "Alice"
}
client = |_| {
    message = !string_append("Hello, ", name)
    _ = perform Alert(message)
    {}
}
page = script(client)
page = !string_to_binary(page)

perform Download({name: "index.html", content: page})
```

More examples in `examples` folder.

The AYG subset would disallow the `perform` keyword.

## Targets

The parser is generated with Antlr, which can create parsers in multiple languages. So far, Java is tested.

## Setup

* JDK 16+

```sh
cd java-parser

./gradlew test
```
