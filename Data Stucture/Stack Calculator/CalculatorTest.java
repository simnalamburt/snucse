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
                .map(token -> token.toString())
                .collect(Collectors.joining(" "))
            );
    }
}

// Parser
class Parser {
    public static enum Type { Number, Operator, Whitespace }

    private final List<Token<Type>> tokens;
    public Parser(List<Token<Type>> tokens) { this.tokens = tokens; }

    // Alternatives for `tokens.get(idx)` function which is exception-safe
    private Optional<Token<Type>> tokenAt(int index) {
        if (index < 0 || index >= tokens.size()) {
            return of(tokens.get(index));
        } else {
            return empty();
        }
    }

    // Missing `or` function for Optional<T>
    private static <T> Optional<T> or(Optional<T> left, Optional<T> right) {
        return left.isPresent() ? left
            : right.isPresent() ? right
            : empty();
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

    private Optional<Integer> tryExpr(int cursor) {
        return or(
            of(cursor)
                .flatMap(this::tryTerm)
                .flatMap(tryOp("+", "-"))
                .flatMap(this::tryExpr),
            of(cursor)
                .flatMap(this::tryTerm)
        );
    }

    private Optional<Integer> tryTerm(int cursor) {
        return or(
            of(cursor)
                .flatMap(this::trySignedFactor)
                .flatMap(tryOp("*", "/", "%"))
                .flatMap(this::tryTerm),
            of(cursor)
                .flatMap(this::trySignedFactor)
        );
    }

    private Optional<Integer> trySignedFactor(int cursor) {
        return or(
            of(cursor)
                .flatMap(tryOp("-"))
                .flatMap(this::trySignedFactor),
            of(cursor)
                .flatMap(this::tryFactor)
        );
    }

    private Optional<Integer> tryFactor(int cursor) {
        return or(
            of(cursor)
                .flatMap(this::tryElement)
                .flatMap(tryOp("^"))
                .flatMap(this::tryFactor),
            of(cursor)
                .flatMap(this::tryElement)
        );
    }

    private Optional<Integer> tryElement(int cursor) {
        return or(
            of(cursor)
                .flatMap(tryOp("("))
                .flatMap(this::tryExpr)
                .flatMap(tryOp(")")),
            of(cursor)
                .flatMap(this::tryNumber)
        );
    }

    private Function<Integer, Optional<Integer>> tryOp(String... ops) {
        return cursor -> tokenAt(cursor)
            .filter(t -> t.kind == Type.Operator)
            .filter(t -> Arrays.asList(ops).contains(t.sequence))
            .map(t -> cursor + 1);
    }

    private Optional<Integer> tryNumber(int cursor) {
        return tokenAt(cursor)
            .filter(t -> t.kind == Type.Number)
            .map(t -> cursor + 1);
    }
}
