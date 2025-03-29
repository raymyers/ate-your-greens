package org.raymyers.ayg;

import eyg.EygLexer;
import eyg.EygParser;
import org.antlr.v4.runtime.*;

import java.util.ArrayList;
import java.util.List;

public class EygTransformer {
    public static ParseResult parse(String code) {
        EygLexer lexer = new EygLexer(CharStreams.fromString(code));
        EygParser parser = new EygParser(new CommonTokenStream(lexer));

        ErrorListener errorListener = new ErrorListener();

        //Remove and Replace Default Console Error Listeners
        lexer.removeErrorListeners();
        parser.removeErrorListeners();
        parser.addErrorListener(errorListener);
        lexer.addErrorListener(errorListener);

        return new ParseResult(parser.program(), errorListener.getSyntaxErrors());
    }
    public record ParseResult(EygParser.ProgramContext program, List<String> syntaxErrors) {
    }
    private static class ErrorListener extends ConsoleErrorListener {

        private final List<String> syntaxErrors = new ArrayList<>();

        @Override
        public void syntaxError(Recognizer<?, ?> recognizer, Object offendingSymbol, int line, int charPositionInLine, String msg, RecognitionException e) {
            syntaxErrors.add(String.format("Syntax Error on %s:%s - %s", line, charPositionInLine, msg));
        }

        public List<String> getSyntaxErrors(){
            return syntaxErrors;
        }
    }

}
