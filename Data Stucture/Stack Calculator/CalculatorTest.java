// TODO: 주석 달기

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

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

class Parser {
    public static enum Type { Number, Operator, Whitespace }
}
