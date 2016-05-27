class AVLTree<K extends Comparable<K>, V> {
    private class Node {
        private K key;
        private V value;
        private Node parent, left, right;
        private int balance;

        private Node(K k, V v) { key = k; value = v; }

        @Override
        public String toString() {
            String ret = key.toString();
            if (left  != null) { ret += ' ' + left .toString(); }
            if (right != null) { ret += ' ' + right.toString(); }
            return ret;
        }

        // 단일 노드의 `this.balance`의 값을 업데이트한다
        private void calc_balance_factor() {
            balance = height(right) - height(left);
        }

        // `this` 이하의 서브트리들을 다시 밸런싱한다.
        private void rebalance() {
            calc_balance_factor();

            Node n;
            if (balance == -2) {
                n = height(this.left.left) >= height(this.left.right) ?
                    rotateRight() :
                    rotateLeftRight();
            } else if (balance == 2) {
                n = height(this.right.right) >= height(this.right.left) ?
                    rotateLeft() :
                    rotateRightLeft();
            } else {
                n = this;
            }

            if (n.parent != null) {
                n.parent.rebalance();
            } else {
                root = n;
            }
        }

        private Node rotateLeft() {
            Node target = this.right;
            target.parent = this.parent;

            this.right = target.left;

            if (this.right != null) { this.right.parent = this; }

            target.left = this;
            this.parent = target;

            if (target.parent != null) {
                if (target.parent.right == this) {
                    target.parent.right = target;
                } else {
                    target.parent.left = target;
                }
            }

            this.calc_balance_factor();
            target.calc_balance_factor();
            return target;
        }

        private Node rotateRight() {
            Node target = this.left;
            target.parent = this.parent;

            this.left = target.right;

            if (this.left != null)
                this.left.parent = this;

            target.right = this;
            this.parent = target;

            if (target.parent != null) {
                if (target.parent.right == this) {
                    target.parent.right = target;
                } else {
                    target.parent.left = target;
                }
            }

            this.calc_balance_factor();
            target.calc_balance_factor();
            return target;
        }

        private Node rotateLeftRight() {
            this.left = this.left.rotateLeft();
            return this.rotateRight();
        }

        private Node rotateRightLeft() {
            this.right = this.right.rotateRight();
            return this.rotateLeft();
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
        boolean validate(Node parent) {
            if (!(this.parent == parent)) { return false; }
            if (!(-1 <= balance && balance <= 1)) { return false; }
            if (left != null) {
                if (!(left.key.compareTo(this.key) < 0)) { return false; }
                if (!left.validate(this)) { return false; }
            }
            if (right != null) {
                if (!(right.key.compareTo(this.key) > 0)) { return false; }
                if (!right.validate(this)) { return false; }
            }
            return true;
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
            parent.rebalance();
            return true;
        }
    }

    V get(K query) {
        if (root == null) { return null; }
        for (Node i = root;;) {
            int cmp = query.compareTo(i.key);
            if (cmp == 0) { return i.value; }

            Node parent = i;
            i = cmp < 0 ? i.left : i.right;
            if (i == null) { return null; }
        }
    }

    private int height(Node n) {
        if (n == null) { return -1; }
        return Math.max(height(n.left), height(n.right)) + 1;
    }

    @Override
    public String toString() { return root == null ? "" : root.toString(); }

    // 올바른 바이너리서치트리인지 검사한다.
    boolean validate() {
        if (root == null) { return true; }

        refresh_balance_factor(root);
        return root.validate(null);
    }

    // 재귀적으로 모든 노드들의 balance factor를 다시 계산한다
    private void refresh_balance_factor(Node node) {
        if (node == null) { return; }
        node.calc_balance_factor();
        refresh_balance_factor(node.left);
        refresh_balance_factor(node.right);
    }
}
