import java.util.ArrayList;

class HybridMap<V> {
    static final int cap = 100;
    public static int hash(String str) {
        int sum = 0;

        int len = str.length();
        for (int i = 0; i < len; ++i) {
            sum += str.charAt(i);
        }
        return sum % cap;
    }

    ArrayList<AVLTree<String, V>> slots;
    HybridMap() {
        slots = new ArrayList<AVLTree<String, V>>();
        for (int i = 0; i < 100; ++i) { slots.add(null); }
    }

    boolean insert(String key, V value) {
        int hash = HybridMap.hash(key);

        AVLTree<String, V> slot = slots.get(hash);

        if (slot == null) {
            // Creating new slot
            AVLTree<String, V> newslot = new AVLTree<String, V>();
            newslot.insert(key, value);
            slots.set(hash, newslot);
            return true;
        } else {
            return slot.insert(key, value);
        }
    }

    V get(String query) {
        int hash = HybridMap.hash(query);

        AVLTree<String, V> slot = slots.get(hash);
        if (slot == null) { return null; }

        return slot.get(query);
    }
}
