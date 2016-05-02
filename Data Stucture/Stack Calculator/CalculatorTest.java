// TODO: 주석 달기

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
import java.util.function.Function;

// Parser
import static java.util.Optional.empty;
import static java.util.Optional.of;

public class CalculatorTest {
    public static void main(final String args[]) {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            try {
                String input = br.readLine();
                if (input == null || input.compareTo("q") == 0) { return; }

                System.out.println(eval(input).orElse("ERROR"));
            } catch (Exception e) {
                System.err.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }

    private static final Lexer<Parser.Type> lexer = new Lexer<Parser.Type>() {{
        add("[0-9]+",           Parser.Type.Number);
        add("[+\\-*\\/%^()]",   Parser.Type.Operator);
        add("[ \t]",            Parser.Type.Whitespace);
    }};

    private static Optional<String> eval(final String input) {
        return lexer.lex(input)
            .map(t -> t.stream()
                .filter(token -> token.kind != Parser.Type.Whitespace)
                .collect(Collectors.toList()))
            .flatMap(Parser::parse)
            .map(t -> t.stream()
                .map(token -> token.toString())
                .collect(Collectors.joining(" "))
            );
    }
}

// Parser
class Parser {
    public static enum Type { Number, Operator, Whitespace }

    public static Optional<List<Token<Type>>> parse(List<Token<Type>> tokens) {
        Parser p = new Parser(tokens);
        Context c0 = new Context();

        return p.tryExpr(c0)
            .filter(c -> c.cursor == tokens.size())
            .map(c -> tokens);
    }

    // Internal class constructor
    private final List<Token<Type>> tokens;
    private Parser(List<Token<Type>> tokens) { this.tokens = tokens; }

    // Alternatives for `tokens.get(idx)` function which is exception-safe
    private Optional<Token<Type>> tokenAt(int index) {
        return 0 <= index && index < tokens.size()
            ? of(tokens.get(index))
            : empty();
    }

    // Missing `or` function for Optional<T>
    private static <T> Optional<T> or(Optional<T> left, Optional<T> right) {
        return left.isPresent() ? left
            : right.isPresent() ? right
            : empty();
    }

    // Parser context
    private static class Context {
        public final int cursor;

        // Create a new empty ctxt
        public Context() { cursor = 0; }

        // Create a new ctxt from existing data
        public Context(int cursor) { this.cursor = cursor; }
    }

    // Parsing rules
    //
    // ```bnf
    //          <expr> ::= <term> | <term> <add-op> <expr>
    //          <term> ::= <signed-factor> | <signed-factor> <mult-op> <term>
    // <signed-factor> ::= <factor> | "-" <signed-factor>
    //        <factor> ::= <element> | <element> "^" <factor>
    //       <element> ::= "(" <expr> ")" | <number>
    //
    //        <add-op> ::= "+" | "-"
    //       <mult-op> ::= "*" | "/" | "%"
    // ```

    private Optional<Context> tryExpr(Context ctxt) {
        return or(
            of(ctxt)
                .flatMap(this::tryTerm)
                .flatMap(tryOp("+", "-"))
                .flatMap(this::tryExpr),
            of(ctxt)
                .flatMap(this::tryTerm)
        );
    }

    private Optional<Context> tryTerm(Context ctxt) {
        return or(
            of(ctxt)
                .flatMap(this::trySignedFactor)
                .flatMap(tryOp("*", "/", "%"))
                .flatMap(this::tryTerm),
            of(ctxt)
                .flatMap(this::trySignedFactor)
        );
    }

    private Optional<Context> trySignedFactor(Context ctxt) {
        return or(
            of(ctxt)
                .flatMap(tryOp("-"))
                .flatMap(this::trySignedFactor),
            of(ctxt)
                .flatMap(this::tryFactor)
        );
    }

    private Optional<Context> tryFactor(Context ctxt) {
        return or(
            of(ctxt)
                .flatMap(this::tryElement)
                .flatMap(tryOp("^"))
                .flatMap(this::tryFactor),
            of(ctxt)
                .flatMap(this::tryElement)
        );
    }

    private Optional<Context> tryElement(Context ctxt) {
        return or(
            of(ctxt)
                .flatMap(tryOp("("))
                .flatMap(this::tryExpr)
                .flatMap(tryOp(")")),
            of(ctxt)
                .flatMap(this::tryNumber)
        );
    }

    private Function<Context, Optional<Context>> tryOp(String... ops) {
        return ctxt -> tokenAt(ctxt.cursor)
            .filter(t -> t.kind == Type.Operator)
            .filter(t -> Arrays.asList(ops).contains(t.sequence))
            .map(t -> new Context(ctxt.cursor + 1));
    }

    private Optional<Context> tryNumber(Context ctxt) {
        return tokenAt(ctxt.cursor)
            .filter(t -> t.kind == Type.Number)
            .map(t -> new Context(ctxt.cursor + 1));
    }
}
