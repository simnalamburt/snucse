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
            return left.smallestLeaf();
        }

        @Override
        public String toString() {
            String ret = Integer.toString(data);
            if (left != null) { ret += ' ' + left.toString(); }
            if (right != null) { ret += ' ' + right.toString(); }
            return ret;
        }

        void insert(int child) {
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
        void delete(int query) {
            Node selected = query < data ? left : right;

            if (_delete_check(selected, query)) { return; }
            // selected.data == query; selected 노드를 지우기

            // Case 1: selected.children = []
            if (selected.isLeaf()) {
                if (query < data) { left = null; } else { right = null; }
            }

            // Case 2: selected.children = [x]
            Node onlyson = selected.onlySon();
            if (onlyson != null) {
                if (query < data) { left = onlyson; } else { right = onlyson; }
            }

            // Case 3: selected.children = [left, right]
            Node smallest = selected.right.smallestLeaf();
            selected.data = smallest.data;
            selected.right.delete(query);
        }
    }

    // Postcondition: node.data == query
    static boolean _delete_check(Node node, int query) {
        if (node == null) { return true; }
        if (node.data != query) { node.delete(query); return true; }
        return false;
    }

    private Node root;
    public BinSearchTree() { root = null; }

    public void insert(int child) {
        // On first insertion
        if (root == null) {
            root = new Node(child);
            return;
        }

        root.insert(child);
    }

    public void delete(int query) {
        // 트리에 없는 숫자를 delete하라고 하진 않는다고 가정되어있음

        if (_delete_check(root, query)) { return; }
        // root.data == query; root 노드 지우기

        // Case 1: root.children = []
        if (root.isLeaf()) {
            root = null;
        }

        // Case 2: root.children = [x]
        Node onlyson = root.onlySon();
        if (onlyson != null) {
            root = onlyson;
        }

        // Case 3: root.children = [left, right]
        Node smallest = root.right.smallestLeaf();
        root.data = smallest.data;
        root.right.delete(query);
    }

    public String search(int data) {
        // TODO: if found node, return the step
        // TODO: if not found, return NONE
        return "NONE";
    }

    @Override
    public String toString(){
        if (root == null) { return ""; }

        return root.toString();
    }
}
