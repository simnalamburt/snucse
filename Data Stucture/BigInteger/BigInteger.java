import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class BigInteger {
    // 부호
    final boolean positive;

    // BigInteger의 숫자정보가 저장되는 배열이다.
    // 배열의 원소 하나당 10진수의 한 자리수에 해당하는 숫자가 저장되어있다.
    //
    // - byte[000] 가 가장 낮은 자리
    // - byte[255] 가 가장 높은 자리
    final byte[] data;

    // 숫자로 구성된 문자열을 받아 BigInteger 객체를 생성한다
    public BigInteger(String s) {
        final char first = s.charAt(0);
        if (first == '+' || first == '-') { s = s.substring(1); }

        positive = first != '-';
        data = new byte[256];

        final int len = s.length();
        for (int i = len - 1, idx = 0; i >= 0; --i, ++idx) {
            char ch = s.charAt(i);
            if (ch < '0' || '9' < ch) { throw new IllegalArgumentException(); }
            data[idx] = (byte)(ch - '0');
        }
    }

    // 이미 초기화된 필드들을 받아 BigInteger 객체를 생성한다
    public BigInteger(boolean positive, byte[] data) {
        this.positive = positive;
        this.data = data.clone();
    }

    // 비교
    //
    // a.cmp(b) == Ordering.Greater    means    a >  b
    // a.cmp(b) == Ordering.Equal      means    a == b
    // a.cmp(b) == Ordering.Less       means    a <  b
    public static enum Ordering { Less, Greater, Equal };
    public Ordering cmp(BigInteger right) {
        int idx = data.length - 1;
        for (; idx >= 0; --idx) {
            byte lhs = this.data[idx],
                 rhs = right.data[idx];
            if (lhs == rhs) { continue; }

            if (lhs < rhs) { return Ordering.Less; }
            if (lhs > rhs) { return Ordering.Greater; }
        }
        return Ordering.Equal;
    }

    // Unary `-` operator
    public BigInteger neg() { return new BigInteger(!positive, data); }

    // Binary `+` operator
    public BigInteger add(BigInteger right) {
        // Handle sign
        if (this.positive) {
            if (right.positive) { }
            else { return this.sub(right.neg()); }
        } else {
            if (right.positive) { return right.sub(this.neg()); }
            else { return (this.neg().add(right.neg())).neg(); }
        }

        // Constraint: this.positive == right.positive == true

        byte carry = 0;
        byte[] data = new byte[this.data.length];

        for (int idx = 0; idx < data.length; ++idx) {
            byte digit = (byte)(this.data[idx] + right.data[idx] + carry);

            // Handle carry
            if (10 <= digit) {
                carry = 1;
                digit -= 10;
            } else {
                carry = 0;
            }

            data[idx] = digit;

            // Debug purpose
            if (digit < 0) { System.err.println((char)27 + "[31mFATAL: Digit was negative" + (char)27 + "[0m"); }
        }

        return new BigInteger(true, data);
    }

    // Binary `-` operator
    public BigInteger sub(BigInteger right) {
        // Handle sign
        if (this.positive) {
            if (right.positive) { }
            else { return this.add(right.neg()); }
        } else {
            if (right.positive) { return (this.neg().add(right)).neg(); }
            else { return right.neg().sub(this.neg()); }
        }

        // Constraint: this.positive == right.positive == true

        Ordering cmp = this.cmp(right);
        if (cmp == Ordering.Equal) { return new BigInteger("0"); }
        if (cmp == Ordering.Less) { return (right.sub(this)).neg(); }

        // Constraint: this > right

        byte carry = 0;
        byte[] data = new byte[this.data.length];

        for (int idx = 0; idx < data.length; ++idx) {
            int digit = this.data[idx] - right.data[idx] - carry;

            // Handle carry
            if (digit < 0) {
                carry = 1;
                digit += 10;
            } else {
                carry = 0;
            }

            data[idx] = (byte)digit;

            // Debug purpose
            if (10 <= digit) { System.err.println((char)27 + "[31mFATAL: Digit was greater than 10" + (char)27 + "[0m"); }
        }

        return new BigInteger(true, data);
    }

    public BigInteger mul(BigInteger right) {
        byte[] data = new byte[this.data.length];

        int carry = 0;
        for (int idx = 0; idx < data.length; ++idx) {
            int sum = carry;
            for (int i = 0; i <= idx; ++i) {
                sum += this.data[i]*right.data[idx - i];
            }

            carry = sum / 10;
            data[idx] = (byte)(sum % 10);
        }

        return new BigInteger(this.positive == right.positive, data);
    }

    @Override
    public String toString() {
        int idx = data.length - 1;
        for (; idx >= 0 && data[idx] == 0; --idx) { } // Skip zeros
        if (idx == -1) { return "0"; }

        StringBuffer buf = new StringBuffer();
        if (!positive) { buf.append('-'); }
        for (; idx >= 0; --idx) { buf.append(data[idx]); }
        return buf.toString();
    }

    private static final Pattern regex = Pattern.compile(
            "\\s*([+-]?)\\s*(\\d+)\\s*([+\\-*])\\s*([+-]?)\\s*(\\d+)\\s*");
    //           '-----'    '----'    '-------'    '-----'    '----'
    //           1 sign     2 lhs    3 operator    4 sign     5 rhs

    static BigInteger evaluate(String input) throws IllegalArgumentException {
        final Matcher m = regex.matcher(input);
        if (!m.matches()) { throw new IllegalArgumentException(); }

        final String lhs_sign = m.group(1),
                     operator = m.group(3),
                     rhs_sign = m.group(4);

        if (operator.length() != 1) { throw new IllegalArgumentException(); }
        final char op       = operator.charAt(0);

        if (lhs_sign.length() > 1) { throw new IllegalArgumentException(); }
        if (rhs_sign.length() > 1) { throw new IllegalArgumentException(); }

        final BigInteger lhs = new BigInteger(lhs_sign + m.group(2)),
                         rhs = new BigInteger(rhs_sign + m.group(5));

        switch (op) {
        case '+': return lhs.add(rhs);
        case '-': return lhs.sub(rhs);
        case '*': return lhs.mul(rhs);
        default: throw new IllegalArgumentException();
        }
    }


    //
    // Entry point
    //
    public static void main(String[] args) throws IOException {
        try (InputStreamReader isr = new InputStreamReader(System.in)) {
            try (BufferedReader reader = new BufferedReader(isr)) {
                try { while (processInput(reader.readLine())) { } }
                catch (IllegalArgumentException e) {
                    System.err.println("입력이 잘못되었습니다.");
                    System.exit(1);
                }
            }
        }
    }

    static boolean processInput(String input) throws IllegalArgumentException {
        if (isQuitCmd(input)) { return false; }

        BigInteger result = evaluate(input);
        System.out.println(result.toString());

        return true;
    }

    static boolean isQuitCmd(String input) {
        if (input == null) { return true; }
        return input.equalsIgnoreCase("quit");
    }
}
