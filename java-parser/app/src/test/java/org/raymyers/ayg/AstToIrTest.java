package org.raymyers.ayg;

import org.junit.jupiter.api.Test;

import java.io.IOException;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ArgumentsSource;
import org.junit.jupiter.api.extension.ExtensionContext;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.ArgumentsProvider;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.core.type.TypeReference;

import java.io.InputStream;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.StringJoiner;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

public class AstToIrTest {

    static class TestExample {
        private String name;
        private String code;
        private Map<String, Object> source;

        // Default constructor for Jackson
        public TestExample() {}

        public TestExample(String name, String code, Map<String, Object> source) {
            this.name = name;
            this.code = code;
            this.source = source;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public String getCode() {
            return code;
        }

        public void setCode(String code) {
            this.code = code;
        }

        public Map<String, Object> getSource() {
            return source;
        }

        public void setSource(Map<String, Object> source) {
            this.source = source;
        }
    }

    @DisplayName("Test parsing EYG IR examples")
    @ParameterizedTest(name = "{0}")
    @ArgumentsSource(IrExamplesProvider.class)
    void testIrParsing(TestExample example) throws IOException {
        if (Set.of("binary", "vacant", "no match").contains(example.name)) {
            // skip
            return;
        }
        EygTransformer.ParseResult result = EygTransformer.parse(example.getCode());
        assertNotNull(result.program());
        assertTrue(result.syntaxErrors().isEmpty(), example.getName() + " : " + result.syntaxErrors().toString());
        // Parse the code and transform to IR
//        Map<String, Object> actualIr = AstToIr.parseAndTransform(example.getCode());

        // Assert that the actual IR matches the expected source
//        assertNotNull(actualIr, "Parsed IR should not be null");
//        assertEquals(example.getSource(), actualIr.get("source"),
//                "The source part of the IR should match the expected source for: " + example.getName());
    }

    static class IrExamplesProvider implements ArgumentsProvider {
        @Override
        public Stream<? extends Arguments> provideArguments(ExtensionContext context) throws IOException {
            // Load examples from JSON resource file
            ObjectMapper mapper = new ObjectMapper();
            InputStream inputStream = getClass().getClassLoader().getResourceAsStream("ir-fixture.json");

            if (inputStream == null) {
                throw new IllegalArgumentException("Resource file 'ir-fixture.json' not found");
            }

            List<TestExample> examples = mapper.readValue(
                    inputStream,
                    new TypeReference<List<TestExample>>() {});

            return examples.stream()
                    .map(example -> Arguments.of(example));
        }
    }

    @Test
    @DisplayName("Test loading the resource file")
    void testResourceLoading() throws IOException {
        InputStream inputStream = getClass().getClassLoader().getResourceAsStream("ir-fixture.json");
        assertNotNull(inputStream, "Should be able to load the ir-fixture.json resource");

        ObjectMapper mapper = new ObjectMapper();
        List<TestExample> examples = mapper.readValue(
                inputStream,
                new TypeReference<List<TestExample>>() {});

        assertNotNull(examples, "Should be able to parse the JSON");
        assertEquals(21, examples.size(), "Should have 21 examples");
    }
}