import java.io.*;
import java.util.*;
import java.nio.file.*;
import java.nio.charset.Charset;

public class Matching {
    public static void main(String args[]) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            try {
                String input = br.readLine();
                if (input == null) { break; } // Handle EOF properly
                if (input.compareTo("QUIT") == 0) { break; }
                if (input.length() < 2) { continue; }

                char cmd = input.charAt(0);
                String param = input.substring(2);

                switch (cmd) {
                case '<': input(param); break;
                case '@':
                    // TODO: Remove below
                    System.out.printf("\u001B[38;5;241m슬롯 \"%s\"\u001B[0m\n", param);
                    break;
                case '?':
                    // TODO: Remove below
                    System.out.printf("\u001B[38;5;241m패턴매칭 \"%s\"\u001B[0m\n", param);
                    break;
                }
            } catch (IOException e) {
                System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }

    static void input(String filename) throws IOException {
        System.out.printf("\u001B[38;5;241m데이터 입력 \"%s\"\u001B[0m\n", filename);
        List<String> lines = Files.readAllLines(Paths.get(filename), Charset.forName("US-ASCII"));

        for (String line : lines) {
            final int len = line.length();
            for (int i = 0; i <= len - 6; ++i) {
                String slice = line.substring(i, i + 6);
                int hash = (
                    slice.charAt(0) +
                    slice.charAt(1) +
                    slice.charAt(2) +
                    slice.charAt(3) +
                    slice.charAt(4) +
                    slice.charAt(5) ) % 100;

                System.out.printf("\u001B[38;5;241m%s\u001B[0m", line.substring(0, i));
                System.out.print(slice);
                System.out.printf("\u001B[38;5;241m%s\u001B[0m (%d)\n",
                        line.substring(i + 6), hash);
            }
        }
    }

    // TODO: Implement
    static AVLTree<Integer, ArrayList<Pair<Integer, Integer>>> map = new AVLTree<Integer, ArrayList<Pair<Integer, Integer>>>();
    private static void command(String line) {
        int input;
        try {
            input = Integer.parseInt(line);
        } catch(NumberFormatException e) {
            System.out.println("\u001B[38;5;241mParse Error\u001B[0m");
            return;
        }

        ArrayList<Pair<Integer, Integer>> entry = map.get(input);
        if (entry == null) {
            // New entry
            ArrayList<Pair<Integer, Integer>> value = new ArrayList<Pair<Integer, Integer>>();
            value.add(Pair.of(input, input));

            boolean ret = map.insert(input, value);

            if (!ret) { System.out.println("\u001B[31mSomething went wrong\u001B[0m"); }
        } else {
            // Dup
            entry.add(Pair.of(input, input));
        }

        if (!map.validate()) { System.out.println("\u001B[31mInvalid AVL Tree\u001B[0m"); }
        System.out.printf("\u001B[33m%s\u001B[0m", map);
        System.out.println();
    }
}
