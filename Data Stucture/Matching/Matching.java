import java.io.*;

class AVLTree<K extends Comparable<K>, V> {
    private class Node {
        private K key;
        private V value;
        private Node parent, left, right;

        private Node(K k, V v) { key = k; value = v; }

        @Override
        public String toString() {
            String ret = key.toString();
            if (left != null) { ret = left.toString() + ' ' + ret; }
            if (right != null) { ret += ' ' + right.toString(); }
            return ret;
        }

        // BST의 부모자식 포인터가 서로 상대방을 올바르게 가리키고있는지, BST의
        // 노드들이 바이너리서치트리의 Invariant를 제대로 만족하고있는지
        // 검사한다.
        //
        // ```java
        // root.validate(null);
        //
        // node.validate(p);
        // ```
        //
        // 위와 같이 호출할경우, `node`의 부모가 `p`가 맞는지 여부를 검사한 뒤,
        // node를 루트로 하는 BST가 올바른 트리인지 검사하게된다.
        //
        // TODO: AVLTree invariant 만족 여부 검증
        boolean validate(Node parent) {
            return this.parent == parent &&
                (left  == null || (left .key.compareTo(this.key) < 0 && left .validate(this))) &&
                (right == null || (right.key.compareTo(this.key) > 0 && right.validate(this)));
        }
    }

    Node root = null;

    boolean insert(K key, V value) {
        // New node which will be inserted
        Node n = new Node(key, value);

        // Check if initial insertion
        if (root == null) { root = n; return true; }

        for (Node i = root;;) {
            int cmp = key.compareTo(i.key);
            if (cmp == 0) { return false; }

            Node parent = i;
            i = cmp < 0 ? i.left : i.right;
            if (i != null) { continue; }

            if (cmp < 0) { parent.left = n; }
            else { parent.right = n; }
            n.parent = parent;
            // TODO: parent.rebalance();
            return true;
        }
    }

    @Override
    public String toString() { return root == null ? "" : root.toString(); }

    // 올바른 바이너리서치트리인지 검사한다.
    //
    // TODO: AVLTree invariant 만족여부 확인하기
    boolean validate() { return root == null || root.validate(null); }
}

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
        int input = Integer.parseInt(line);
        boolean inserted = map.insert(input, null);

        // TODO: Remove debug codes
        System.out.printf("\u001B[33m%s\u001B[0m", map);
        if (inserted) { System.out.printf(" (Inserted %d)", input); }
        System.out.println();
        if (!map.validate()) { System.out.println("\u001B[31mInvalid BST warning\u001B[0m"); }
    }
}
