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

                command(input);
            } catch (Exception e) {
                System.err.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }

    private static enum Type { Number, Operator, Whitespace }
    private static final Lexer<Type> lexer = new Lexer<Type>() {{
        add("[0-9]+", Type.Number);
        add("[+\\-*\\/%^()]", Type.Operator);
        add("[ \t]", Type.Whitespace);
    }};

    private static void command(final String input) {
        Optional<ArrayList<Token<Type>>> result = lexer.lex(input);

        String msg = result
            .map((ArrayList<Token<Type>> tokens) ->
                    tokens.stream()
                    .filter(token -> token.kind != Type.Whitespace)
                    .map(token -> token.toString())
                    .collect(Collectors.joining(" "))
            )
            .orElse("ERROR");

        System.out.println(msg);

        // TODO: Implement
    }
}
