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
        positive = true; // TODO
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

    // Unary `-` operator
    public BigInteger neg() { return new BigInteger(!positive, data); }

    // Binary `+` operator
    public BigInteger add(BigInteger rhs) {
        // TODO: 부호 처리

        byte[] data = this.data.clone();

        // Constraint: this.positive == rhs.positive == true
        byte carry = 0;
        for (int idx = 0; idx < data.length; ++idx) {
            byte digit = (byte)(data[idx] + rhs.data[idx] + carry);

            // Handle carry
            if (digit >= 10) {
                carry = 1;
                digit -= 10;
            }

            data[idx] = digit;
        }

        return new BigInteger(true, data);
    }

    public BigInteger subtract(BigInteger big) {
        // TODO
        return this;
    }

    public BigInteger multiply(BigInteger big) {
        // TODO
        return this;
    }

    @Override
    public String toString() {
        StringBuffer buf = new StringBuffer();

        int idx = data.length - 1;
        for (; idx >= 0 && data[idx] == 0; --idx) { } // Skip zeros
        for (; idx >= 0; --idx) { buf.append(data[idx]); }

        return buf.toString();
    }

    static BigInteger evaluate(String input) throws IllegalArgumentException
    {
        // TODO: Remove below
        return new BigInteger(input);

        // TODO
        // implement here
        // parse input
        // using regex is allowed
        // Pattern EXPRESSION_PATTERN = Pattern.compile("");
        //
        // 숫자 앞뒤 연산자 앞뒤 공백
        // 탭, 스페이스, 등

        // One possible implementation
        // BigInteger num1 = new BigInteger(arg1);
        // BigInteger num2 = new BigInteger(arg2);
        // BigInteger result = num1.add(num2);
        // return result;
    }

    public static void main(String[] args) throws Exception
    {
        try (InputStreamReader isr = new InputStreamReader(System.in))
        {
            try (BufferedReader reader = new BufferedReader(isr))
            {
                boolean done = false;
                while (!done)
                {
                    String input = reader.readLine();

                    try
                    {
                        done = processInput(input);
                    }
                    catch (IllegalArgumentException e)
                    {
                        System.err.println("입력이 잘못되었습니다.");
                    }
                }
            }
        }
    }

    static boolean processInput(String input) throws IllegalArgumentException
    {
        boolean quit = isQuitCmd(input);

        if (quit)
        {
            return true;
        }
        else
        {
            BigInteger result = evaluate(input);
            System.out.println(result.toString());

            return false;
        }
    }

    static boolean isQuitCmd(String input) {
        if (input == null) { return true; }
        return input.equalsIgnoreCase("quit");
    }
}
