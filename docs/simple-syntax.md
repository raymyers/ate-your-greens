# Simple Syntax

This is a slightly more verbose syntax that is easier to implement parsers for.

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

## Differences

* `let` keyword
* `case` keyword
* Semi-colons after `let` statements
