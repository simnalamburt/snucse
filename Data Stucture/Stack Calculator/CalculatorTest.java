import java.io.*;
import java.util.*;
import java.util.stream.Stream;
import java.util.stream.Collectors;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
    private static final Lexer lexer = new Lexer<Type>() {{
        add("[0-9]+", Type.Number);
        add("[+\\-*\\/%^()]", Type.Operator);
        add("[ \t]", Type.Whitespace);
    }};

    private static void command(final String input) {
        // TODO: warning: [unchecked] unchecked conversion
        Optional<ArrayList<Token<Type>>> result = lexer.lex(input);
        //                                                 ^
        //   required: Optional<ArrayList<Token<Type>>>
        //   found:    Optional

        String msg = result
            .map((ArrayList<Token<Type>> tokens) ->
                    tokens.stream()
                    .filter(token -> token.kind != Type.Whitespace)
                    .map(token -> token.kind+"("+token.sequence+")")
                    .collect(Collectors.joining(" "))
            )
            .orElse("ERROR");

        System.out.println(msg);

        // TODO: Implement
    }
}

class Lexer<E> {
    final ArrayList<Rule<E>> rules = new ArrayList<Rule<E>>();

    public void add(final String rule, final E kind) {
        rules.add(new Rule<E>(rule, kind));
    }

    public Optional<ArrayList<Token<E>>> lex(String input) {
        ArrayList<Token<E>> result = new ArrayList<Token<E>>();

        while (!input.isEmpty()) {
            boolean failed = true;
            for (Rule<E> rule : rules) {
                Matcher m = rule.regex.matcher(input);
                if (!m.find()) { continue; }

                failed = false;
                result.add(new Token<E>(m.group(), rule.kind));
                input = m.replaceFirst("");
                break;
            }
            // 렉싱에 실패한경우, empty 반환
            if (failed) { return Optional.empty(); }
        }

        // 렉싱 결과물 반환
        return Optional.of(result);
    }
}

class Rule<E> {
    public final Pattern regex;
    public final E kind;

    public Rule(final String rule, final E kind) {
        this.regex = Pattern.compile("^("+rule+")");
        this.kind = kind;
    }
}

class Token<E> {
    public final String sequence;
    public final E kind;

    public Token(final String sequence, final E kind) {
        this.sequence = sequence;
        this.kind = kind;
    }
}
