import java.io.*;

public class Matching {
    public static void main(String args[]) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            try {
                String input = br.readLine();
                if (input == null) { break; } // Handle EOF properly
                if (input.compareTo("QUIT") == 0) { break; }
                if (input.compareTo("") == 0) { continue; } // Ignore empty line

                command(input);
            } catch (IOException e) {
                System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }

    // TODO: Implement
    static AVLTree<Integer, Void> map = new AVLTree<Integer, Void>();
    private static void command(String line) {
        int input;
        try {
            input = Integer.parseInt(line);
        } catch(NumberFormatException e) {
            System.out.println("\u001B[38;5;241mParse Error\u001B[0m");
            return;
        }
        boolean inserted = map.insert(input, null);

        // TODO: Remove debug codes
        System.out.printf("\u001B[33m%s\u001B[0m", map);
        if (inserted) { System.out.printf(" (Inserted %d)", input); }
        System.out.println();
        if (!map.validate()) { System.out.println("\u001B[31mInvalid BST warning\u001B[0m"); }
    }
}
