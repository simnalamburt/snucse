public class BinSearchTree {
    private class Node {
        private Node left, right;
        private int data;

        Node(int data) {
            right = left = null;
            this.data = data;
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

    public void delete(int data) {
        // 없는걸 delete하진 않음

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
