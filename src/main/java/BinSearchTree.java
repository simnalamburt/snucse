public class BinSearchTree {
    private Node root;

    public BinSearchTree() {
        root = null;
    }

    private class Node {
        private Node left;
        private Node right;
        private int data;
        Node(int data) {
            right = null;
            left = null;
            this.data = data;
        }
    }

    public void insert(int data) {
        // TODO: insert node
    }

    public void delete(int data) {
        // TODO: delete target node
    }
    public String search(int data) {
        // TODO: if found node, return the step
        // TODO: if not found, return NONE
        return "NONE";
    }

    @Override
    public String toString(){
        // TODO: preorder print
        return "";
    }
}
