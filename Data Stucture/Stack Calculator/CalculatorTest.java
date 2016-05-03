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

    private static final Lexer<Type> lexer = new Lexer<Type>() {{
        add("[0-9]+",           Type.Number);
        add("[+\\-*\\/%^()]",   Type.Operator);
        add("[ \t]",            Type.Whitespace);
    }};

    private static Optional<String> eval(final String input) {
        // TODO: 익셉션 핸들링
        return lexer.lex(input)
            .map(t -> t.stream()
                .filter(token -> token.kind != Type.Whitespace)
                .collect(Collectors.toList()))
            .flatMap(Parser::parse)
            .flatMap(Calc::calc)
            .map(t -> t.postfix.stream()
                .map(token -> token.sequence)
                .collect(Collectors.joining(" ")) + "\n" + t.result);
    }
}

// Parser
enum Type { Number, Operator, Whitespace }

class Parser {
    public static Optional<List<Token<Type>>> parse(List<Token<Type>> tokens) {
        Parser p = new Parser(tokens);
        Context c0 = new Context();

        return p.tryExpr(c0)
            .filter(c -> c.cursor == tokens.size())
            .map(c -> c.terminate())
            .map(c -> c.output);
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
    //
    // Reference: Shunting-yard Algorithm
    private static class Context {
        public final int cursor;
        public final ArrayList<Token<Type>> output;
        public final ArrayList<Token<Type>> op_stack;

        private Context(int cursor,
                ArrayList<Token<Type>> output,
                ArrayList<Token<Type>> op_stack)
        {
            this.cursor = cursor;
            this.output = output;
            this.op_stack = op_stack;
        }

        public Context() {
            cursor = 0;
            output = new ArrayList<Token<Type>>();
            op_stack = new ArrayList<Token<Type>>();
        }

        public Context push(Token<Type> t) {
            switch (t.kind) {
            case Number: {
                final ArrayList<Token<Type>> output = new ArrayList<Token<Type>>(this.output) {{
                    add(t);
                }};

                return new Context(cursor + 1, output, op_stack); }
            case Operator: {
                final ArrayList<Token<Type>>
                    output = new ArrayList<Token<Type>>(this.output),
                    op_stack = new ArrayList<Token<Type>>(this.op_stack);

                switch (t.sequence) {
                case "(":
                    op_stack.add(t);
                    break;
                case ")":
                    while (true) {
                        if (op_stack.isEmpty()) { throw new IllegalArgumentException(); }

                        Token<Type> pop = op_stack.remove(op_stack.size() - 1);
                        if (pop.sequence.equals("(")) { break; }

                        output.add(pop);
                    }
                    break;
                default:
                    while (!op_stack.isEmpty()) {
                        Token<Type> top = op_stack.get(op_stack.size() - 1);
                        boolean condition = !top.sequence.equals("(") &&
                            ( is_left_assoc(t)
                            ? precedence(t) <= precedence(top)
                            : precedence(t) < precedence(top) );

                        if (!condition) { break; }

                        output.add(top);
                        op_stack.remove(op_stack.size() - 1);
                    }

                    op_stack.add(t);
                }

                return new Context(cursor + 1, output, op_stack); }
            default:
                return this;
            }
        }

        public Context terminate() {
            final ArrayList<Token<Type>>
                output = new ArrayList<Token<Type>>(this.output),
                op_stack = new ArrayList<Token<Type>>(this.op_stack);

            while (!op_stack.isEmpty()) {
                Token<Type> t = op_stack.remove(op_stack.size() - 1);
                output.add(t);
            }

            return new Context(cursor, output, op_stack);
        }

        private static int precedence(Token<Type> op) {
            switch (op.sequence) {
            case "^":                       return 4;
            case "~":                       return 3;
            case "*": case "/": case "%":   return 2;
            case "+": case "-":             return 1;
            default: throw new IllegalArgumentException();
            }
        }

        private static boolean is_left_assoc(Token<Type> op) {
            switch (op.sequence) {
            case "*": case "/": case "%":
            case "+": case "-":             return true;
            case "^": case "~":             return false;
            default: throw new IllegalArgumentException();
            }
        }
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
                .flatMap(this::tryUnaryMinus)
                .flatMap(this::trySignedFactor),
            of(ctxt)
                .flatMap(this::tryFactor)
        );
    }

    private Optional<Context> tryUnaryMinus(Context ctxt) {
        return tokenAt(ctxt.cursor)
            .filter(t -> t.kind == Type.Operator)
            .filter(t -> t.sequence.equals("-"))
            .map(t -> new Token<Type>("~", Type.Operator))
            .map(ctxt::push);
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
            .map(ctxt::push);
    }

    private Optional<Context> tryNumber(Context ctxt) {
        return tokenAt(ctxt.cursor)
            .filter(t -> t.kind == Type.Number)
            .map(ctxt::push);
    }
}

// Calc
class Calc {
    static Optional<CalcResult> calc(List<Token<Type>> postfix) {
        Stack<Long> operands = new Stack<Long>();

        for (Token<Type> token: postfix) {
            switch (token.kind) {
            case Number:
                operands.push(Long.parseLong(token.sequence));
                break;
            case Operator:
                Long result;

                if (token.sequence.equals("~")) {
                    // Unary operator
                    Long operand = operands.pop();

                    result = -operand;
                } else {
                    // Binary operator
                    Long right = operands.pop();
                    Long left = operands.pop();

                    switch (token.sequence) {
                    case "+": result = left + right; break;
                    case "-": result = left - right; break;
                    case "*": result = left * right; break;
                    case "/":
                        if (right == 0) { return empty(); }
                        result = left / right;
                        break;
                    case "%":
                        if (right == 0) { return empty(); }
                        result = left % right;
                        break;
                    case "^":
                        if (left == 0 && right < 0) { return empty(); }
                        result = (long) Math.pow(left, right);
                        break;
                    default: throw new IllegalArgumentException();
                    }
                }

                operands.push(result);
                break;
            }
        }

        return of(new CalcResult(postfix, operands.pop()));
    }
}

class CalcResult {
    public final List<Token<Type>> postfix;
    public final long result;

    public CalcResult(List<Token<Type>> postfix, long result) {
        this.postfix = postfix;
        this.result = result;
    }
}
