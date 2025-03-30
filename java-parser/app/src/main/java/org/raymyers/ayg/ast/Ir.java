package org.raymyers.ayg.ast;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ObjectNode;

import java.io.IOException;

public class Ir {
    public interface Expression extends Node{ }
    public interface Node { }
    record Variable(String label) implements Expression {}
    record Lambda(String label, Expression body) implements Expression {}
    record Apply(Expression function, Expression body) implements Expression {}
    record Let(String label, Expression value, Expression then) implements Expression {}
    record Binary(String value) implements Expression {}
    record Integer_(String value) implements Expression {}
    record String_(String value) implements Expression {}
    record Tail() implements Expression {}
    record Cons() implements Expression {}
    record Vacant(String comment) implements Expression {}
    record Empty() implements Expression {}
    record Extend(String label) implements Expression {}
    record Select(String label) implements Expression {}
    record Overwrite(String label)  implements Node {}
    record Tag(String label) implements Node {}
    record Case_(String label) implements Node {}
    record NoCases() implements Node {}
    record Perform(String label) implements Expression {}
    record Handle(String label) implements Node {}
    record Shallow(String label) implements Node {}
    record Builtin(String label) implements Node {}
    record Reference(String label) implements Node {}
    record Release(String label, String version, String hash) implements Node {}

//    // variable
//    {"0": "v", "l": label}
//    // lambda(label, body)
//    {"0": "f", "l": label, "b": expression}
//    // apply(function, argument)
//    {"0": "a", "f": expression, "a": expression}
//    // let(label, value, then)
//    {"0": "l", "l": label, "v": expression, "t": expression}
//    // b already taken when adding binary
//    // binary(value)
//    {"0": "x", "v": bytes}
//    // integer(value)
//    {"0": "i", "v": integer}
//    // string(value)
//    {"0": "s", "v": string}
//    // tail
//    {"0": "ta"}
//    // cons
//    {"0": "c"}
//    // vacant(comment)
//    {"0": "z", "c": string}
//    // empty
//    {"0": "u"}
//    // extend(label)
//    {"0": "e", "l": label}
//    // select(label)
//    {"0": "g", "l": label}
//    // overwrite(label)
//    {"0": "o", "l": label}
//    // tag(label)
//    {"0": "t", "l": label}
//    // case(label)
//    {"0": "m", "l": label}
//    // nocases
//    {"0": "n"}
//    // perform(label)
//    {"0": "p", "l": label}
//    // handle(label)
//    {"0": "h", "l": label}
//    // shallow(label)
//    {"0": "hs", "l": label}
//    // builtin(label)
//    {"0": "b", "l": label}
//    // reference(label)
//    {"0": "#", "l": label}
//
//    // release(label)
//    {"0": "@", "p": label, r: integer}

    public static Ir.Node parseNodeFromString(String json) throws IOException {
        JsonNode node = new ObjectMapper().readTree(json);
        return parseNode(node);
    }

    public static Expression parseExpression(JsonNode node) {
        return asExpression(parseNode(node));
    }

    public static Ir.Node parseNode(JsonNode node) {
        if (!node.has("0")) {
            throw new IllegalArgumentException("Invalid expression format: missing type tag '0'");
        }

        String type = node.get("0").asText();

        return switch (type) {
            case "v" -> new Ir.Variable(node.get("l").asText());
            case "f" -> new Ir.Lambda(
                    node.get("l").asText(),
                    parseExpression(node.get("b"))
            );
            case "a" ->
                new Ir.Apply(
                        parseExpression(node.get("f")),
                        parseExpression(node.get("a"))
                );
            case "l" ->
                new Ir.Let(
                        node.get("l").asText(),
                        parseExpression(node.get("v")),
                        parseExpression(node.get("t"))
                );
            case "x" -> new Ir.Binary(parseBytesValue(node));
            case "i" -> new Ir.Integer_(node.get("v").asText());
            case "s" -> new Ir.String_(node.get("v").asText());
            case "ta" -> new Ir.Tail();
            case "c" -> new Ir.Cons();
            case "z" -> new Ir.Vacant(node.has("c") ? node.get("c").asText() : "");
            case "u" -> new Ir.Empty();
            case "e" -> new Ir.Extend(node.get("l").asText());
            case "g" -> new Ir.Select(node.get("l").asText());
            case "o" -> new Ir.Overwrite(node.get("l").asText());
            case "t" -> new Ir.Tag(node.get("l").asText());
            case "m" -> new Ir.Case_(node.get("l").asText());
            case "n" -> new Ir.NoCases();
            case "p" -> new Ir.Perform(node.get("l").asText());
            case "h" -> new Ir.Handle(node.get("l").asText());
            case "hs" -> new Ir.Shallow(node.get("l").asText());
            case "b" -> new Ir.Builtin(node.get("l").asText());
            case "#" -> new Ir.Reference(node.get("l").get("/").asText());
            case "@" -> new Ir.Release(
                    node.get("p").asText(),
                    node.get("r").asText(),
                    node.get("l").get("/").asText());
            default -> throw new IllegalArgumentException("Unknown expression type: " + type);
        };
    }

    private static String parseBytesValue(JsonNode node) {
        JsonNode valNode = node.get("v");
        if (valNode.has("/") && valNode.get("/").has("bytes")) {
            return valNode.get("/").get("bytes").asText();
        }
        return valNode.asText();
    }

    private static Expression asExpression(Node node) {
        // Error message
        return (Expression) node;
    }

    public static JsonNode serializeNode(Ir.Node node) {
        ObjectMapper mapper = new ObjectMapper();
        ObjectNode jsonNode = mapper.createObjectNode();

        if (node instanceof Ir.Variable variable) {
            jsonNode.put("0", "v");
            jsonNode.put("l", variable.label());
        } else if (node instanceof Ir.Lambda lambda) {
            jsonNode.put("0", "f");
            jsonNode.put("l", lambda.label());
            jsonNode.set("b", serializeNode(lambda.body()));
        } else if (node instanceof Ir.Apply apply) {
            jsonNode.put("0", "a");
            jsonNode.set("f", serializeNode(apply.function()));
            jsonNode.set("a", serializeNode(apply.body()));
        } else if (node instanceof Ir.Let let) {
            jsonNode.put("0", "l");
            jsonNode.put("l", let.label());
            jsonNode.set("v", serializeNode(let.value()));
            jsonNode.set("t", serializeNode(let.then()));
        } else if (node instanceof Ir.Binary binary) {
            jsonNode.put("0", "x");
            jsonNode.set("v", binaryValueNode(binary, mapper));
        } else if (node instanceof Ir.Integer_ integer) {
            jsonNode.put("0", "i");
            jsonNode.put("v", Integer.parseInt(integer.value()));
        } else if (node instanceof Ir.String_ string) {
            jsonNode.put("0", "s");
            jsonNode.put("v", string.value());
        } else if (node instanceof Ir.Tail) {
            jsonNode.put("0", "ta");
        } else if (node instanceof Ir.Cons) {
            jsonNode.put("0", "c");
        } else if (node instanceof Ir.Vacant vacant) {
            jsonNode.put("0", "z");
            if (vacant.comment() != null && !vacant.comment().isEmpty()) {
                jsonNode.put("c", vacant.comment());
            }
        } else if (node instanceof Ir.Empty) {
            jsonNode.put("0", "u");
        } else if (node instanceof Ir.Extend extend) {
            jsonNode.put("0", "e");
            jsonNode.put("l", extend.label());
        } else if (node instanceof Ir.Select select) {
            jsonNode.put("0", "g");
            jsonNode.put("l", select.label());
        } else if (node instanceof Ir.Overwrite overwrite) {
            jsonNode.put("0", "o");
            jsonNode.put("l", overwrite.label());
        } else if (node instanceof Ir.Tag tag) {
            jsonNode.put("0", "t");
            jsonNode.put("l", tag.label());
        } else if (node instanceof Ir.Case_ case_) {
            jsonNode.put("0", "m");
            jsonNode.put("l", case_.label());
        } else if (node instanceof Ir.NoCases) {
            jsonNode.put("0", "n");
        } else if (node instanceof Ir.Perform perform) {
            jsonNode.put("0", "p");
            jsonNode.put("l", perform.label());
        } else if (node instanceof Ir.Handle handle) {
            jsonNode.put("0", "h");
            jsonNode.put("l", handle.label());
        } else if (node instanceof Ir.Shallow shallow) {
            jsonNode.put("0", "hs");
            jsonNode.put("l", shallow.label());
        } else if (node instanceof Ir.Builtin builtin) {
            jsonNode.put("0", "b");
            jsonNode.put("l", builtin.label());
        } else if (node instanceof Ir.Reference reference) {
            jsonNode.put("0", "#");
            jsonNode.put("l", reference.label());
            var lVal = mapper.createObjectNode();
            lVal.put("/", reference.label());
            jsonNode.set("l", lVal);
        } else if (node instanceof Ir.Release release) {
            jsonNode.put("0", "@");
            jsonNode.put("p", release.label());
            jsonNode.put("r", Integer.parseInt(release.version()));
            var lVal = mapper.createObjectNode();
            lVal.put("/", release.hash());
            jsonNode.set("l", lVal);
        } else {
            throw new IllegalArgumentException("Unknown node type: " + node.getClass().getName());
        }

        return jsonNode;
    }

    private static ObjectNode binaryValueNode(Binary binary, ObjectMapper mapper) {
        var bVal = mapper.createObjectNode();
        bVal.set("/", mapper.createObjectNode().put("bytes", binary.value));
        return bVal;
    }

    /**
     * Convenience method to serialize an Ir.Node to a JSON string
     *
     * @param node The Ir.Node to serialize
     * @return JSON string representation
     */
    public static String serializeNodeToString(Ir.Node node) throws Exception {
        ObjectMapper mapper = new ObjectMapper();
        return mapper.writeValueAsString(serializeNode(node));
    }
}
