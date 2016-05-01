import java.io.*;

public class CalculatorTest {
    public static void main(String args[]) {
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

    private static void command(String input) {
        // TODO : 아래 문장을 삭제하고 구현해라.
        System.out.println("<< command 함수에서 " + input + " 명령을 처리할 예정입니다 >>");
    }
}
