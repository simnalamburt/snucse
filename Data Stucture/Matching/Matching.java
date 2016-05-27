import java.io.*;
import java.util.ArrayList;

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
    static AVLTree<Integer, ArrayList<Integer>> map = new AVLTree<Integer, ArrayList<Integer>>();
    private static void command(String line) {
        int input;
        try {
            input = Integer.parseInt(line);
        } catch(NumberFormatException e) {
            System.out.println("\u001B[38;5;241mParse Error\u001B[0m");
            return;
        }

        ArrayList<Integer> entry = map.get(input);
        if (entry == null) {
            // New entry
            ArrayList<Integer> value = new ArrayList<Integer>();
            value.add(input);

            boolean ret = map.insert(input, value);

            if (!ret) { System.out.println("\u001B[31mSomething went wrong\u001B[0m"); }
        } else {
            // Dup
            entry.add(input);
        }

        if (!map.validate()) { System.out.println("\u001B[31mInvalid AVL Tree\u001B[0m"); }
        System.out.printf("\u001B[33m%s\u001B[0m", map);
        System.out.println();
    }
}
