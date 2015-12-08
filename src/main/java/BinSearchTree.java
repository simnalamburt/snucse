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
        //insert node
    }

    public void delete(int data) {
        //delete target node
    }
    public String search(int data) {
        //if found node, return the step
        //if not found, return NONE
    }

    public String toString(){
        //preorder print
    }
}
