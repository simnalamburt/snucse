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
                case '@': slot(param); break;
                case '?':
                    // TODO: Remove below
                    System.out.printf("\u001B[38;5;241m패턴매칭 \"%s\"\u001B[0m\n", param);
                    break;
                }
            } catch (IOException e) {
                System.err.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }

    static HybridMap<LinkedList<Pair<Integer, Integer>>> dict;
    static void input(String filename) throws IOException {
        List<String> lines = Files.readAllLines(Paths.get(filename), Charset.forName("US-ASCII"));

        dict = new HybridMap<LinkedList<Pair<Integer, Integer>>>();

        int row = 1;
        for (String line : lines) {
            final int len = line.length();
            for (int i = 0; i <= len - 6; ++i) {
                String slice = line.substring(i, i + 6);
                Pair<Integer, Integer> pos = Pair.of(row, i + 1);

                LinkedList<Pair<Integer, Integer>> entry = dict.get(slice);
                if (entry == null) {
                    // New entry
                    LinkedList<Pair<Integer, Integer>> newentry = new LinkedList<Pair<Integer, Integer>>();
                    newentry.add(pos);

                    dict.insert(slice, entry);
                } else {
                    // Dup
                    entry.add(pos);
                }
            }
            ++row;
        }
    }

    static void slot(String param) {
        int input = Integer.parseInt(param);
        System.out.println(dict.slots.get(input));
    }
}
