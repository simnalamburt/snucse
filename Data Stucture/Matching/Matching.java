import java.io.*;

class AVLTree<K extends Comparable<K>, V> {
    class Node {
        K key;
        V value;
        Node parent, left, right;

        Node(K k, V v) { key = k; value = v; }
    }

    Node root = null;

    void insert(K key, V value) {
        // New node which will be inserted
        Node n = new Node(key, value);

        // Check if initial insertion
        if (root == null) { root = n; return; }

        // Standard BST insertion
        Node y, x = root;
        do {
            y = x;
            x = n.key.compareTo(x.key) < 0 ? x.left : x.right;
        } while (x != null);
        n.parent = y;
        if (n.key.compareTo(y.key) < 0) {
            y.left = n;
        } else {
            y.right = n;
        }

        // TODO: Balancing
    }
}

public class Matching {
    public static void main(String args[]) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            try {
                String input = br.readLine();
                if (input.compareTo("QUIT") == 0) { break; }

                command(input);
            } catch (IOException e) {
                System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }

    // TODO: Implement
    private static void command(String input) {
        System.out.println("<< command 함수에서 " + input + " 명령을 처리할 예정입니다 >>");
    }
}
