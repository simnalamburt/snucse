// 2013-11392 김지현

import java.util.ArrayList;

public class BinSearchTree {
    private class Node {
        private Node left, right;
        public int data;

        Node(int data) {
            right = left = null;
            this.data = data;
        }

        boolean isLeaf() { return left == null && right == null; }

        Node onlySon() {
            if (left == null && right == null) { return null; }
            if (left != null && right != null) { return null; }

            return left != null ? left : right;
        }

        // Postcondition: returned Node is not null
        Node smallestLeaf() {
            if (left == null) { return this; }

            System.out.format(" %d", data);
            return left.smallestLeaf();
        }

        @Override
        public String toString() {
            String ret = Integer.toString(data);
            if (left != null) { ret += ' ' + left.toString(); }
            if (right != null) { ret += ' ' + right.toString(); }
            return ret;
        }

        boolean search(int query, ArrayList<Integer> steps) {
            steps.add(data);

            if (query == data) { return true; }

            Node selected = query < data ? left : right;
            if (selected == null) { return false; }
            return selected.search(query, steps);
        }

        void insert(int child) {
            System.out.format(" %d", data);

            // 낮으면 왼쪽, 같거나 크면 오른쪽
            if (child < data) {
                if (left == null) {
                    left = new Node(child);
                    return;
                }

                left.insert(child);
            } else {
                if (right == null) {
                    right = new Node(child);
                    return;
                }

                right.insert(child);
            }
        }

        // Precondition: data != query
        void delete(int query) { delete(query, true); }
        void delete(int query, boolean verbose) {
            Node selected = query < data ? left : right;

            if (_delete_check(selected, query, verbose)) { return; }
            // selected.data == query; selected 노드를 지우기

            // Case 1: selected.children = []
            if (selected.isLeaf()) {
                if (verbose) { System.out.format(" %d", selected.data); }
                if (query < data) { left = null; } else { right = null; }
            }

            // Case 2: selected.children = [x]
            Node onlyson = selected.onlySon();
            if (onlyson != null) {
                if (verbose) { System.out.format(" %d", selected.data); }
                if (query < data) { left = onlyson; } else { right = onlyson; }
            }

            // Case 3: selected.children = [left, right]
            Node smallest = selected.right.smallestLeaf();
            selected.data = smallest.data;
            if (verbose) { System.out.format(" %d", smallest.data); }
            if (selected.right == smallest) {
                if (selected.right.isLeaf()) { selected.right = null; }
                else { selected.right = selected.right.onlySon(); }
            } else {
                selected.right.delete(smallest.data, false);
            }
        }
    }

    // Postcondition: node.data == query
    static boolean _delete_check(Node node, int query) {
        return _delete_check(node, query, true);
    }
    static boolean _delete_check(Node node, int query, boolean verbose) {
        if (node == null) { return true; }

        if (verbose) { System.out.format(" %d", node.data); }
        if (node.data != query) { node.delete(query); return true; }
        return false;
    }

    private Node root;
    public BinSearchTree() { root = null; }

    public void insert(int child) {
        System.out.format("inserting %d:", child);

        // On first insertion
        if (root == null) {
            root = new Node(child);
        } else {
            root.insert(child);
        }

        System.out.format(" %d\n", child);
    }

    // Precondition: query does exist in the tree
    public void delete(int query) {
        System.out.format("deleting %d:", query);

        try {
            if (_delete_check(root, query)) { return; }
            // root.data == query; root 노드 지우기

            // Case 1: root.children = []
            if (root.isLeaf()) {
                System.out.format(" %d", root.data);
                root = null;
            }

            // Case 2: root.children = [x]
            Node onlyson = root.onlySon();
            if (onlyson != null) {
                System.out.format(" %d", root.data);
                root = onlyson;
            }

            // Case 3: root.children = [left, right]
            Node smallest = root.right.smallestLeaf();
            root.data = smallest.data;
            System.out.format(" %d", smallest.data);
            if (root.right == smallest) {
                if (root.right.isLeaf()) { root.right = null; }
                else { root.right = root.right.onlySon(); }
            } else {
                root.right.delete(smallest.data);
            }
        } finally {
            System.out.println();
        }
    }

    public String search(int query) {
        if (root == null) { return "NONE"; }

        ArrayList<Integer> steps = new ArrayList<Integer>();
        if (!root.search(query, steps)) { return "NONE"; }

        StringBuffer buf = new StringBuffer();
        for (int step: steps) {
            buf.append(step);
            buf.append(' ');
        }

        return buf.toString().trim();
    }

    @Override
    public String toString(){
        if (root == null) { return ""; }

        return root.toString();
    }
}
