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
                case '?': match(param); break;
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

                    dict.insert(slice, newentry);
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
        AVLTree tree = dict.slots.get(input);
        System.out.println(tree == null ? "EMPTY" : tree);
    }

    static void match(String query) {
        if (!try_match(query)) { System.out.println("(0, 0)"); }
    }

    static boolean try_match(String query) {
        // TODO: 최적화

        String first_slice = query.substring(0, 6);
        LinkedList<Pair<Integer, Integer>> first_entry = dict.get(first_slice);
        if (first_entry == null) { return false; }

        final int len = query.length();
        for (int i = 1; i <= len - 6; ++i) {
            String slice = query.substring(i, i + 6);
            LinkedList<Pair<Integer, Integer>> entry = dict.get(slice);
            if (entry == null) { return false; }

            LinkedList<Pair<Integer, Integer>> temp = new LinkedList<Pair<Integer, Integer>>(first_entry);
            for (Pair<Integer, Integer> pos : first_entry) {
                boolean contains = false;
                for (Pair<Integer, Integer> newpos : entry) {
                    if (pos.first + 0 == newpos.first && pos.second + i == newpos.second) {
                        contains = true;
                        break;
                    }
                }

                if (!contains) { temp.remove(pos); }
            }
            first_entry = temp;
        }

        if (first_entry.size() == 0) { return false; }

        StringBuilder buf = new StringBuilder();
        for (Pair pos : first_entry) {
            buf.append(pos.toString());
            buf.append(' ');
        }
        System.out.println(buf.toString().trim());
        return true;
    }
}
