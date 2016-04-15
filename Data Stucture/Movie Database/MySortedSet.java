public class MySortedSet<E extends Comparable<E>> extends MyLinkedList<E> {
    @Override
    public void add(E elem) {
        Node<E> target = super.head;
        while (true) {
            Node<E> next = target.getNext();
            if (next == null) { break; }

            int ret = elem.compareTo(next.item);
            if (ret == 0) { return; }
            if (ret < 0) { break; }

            target = next;
        }

        target.insertNext(elem);
        super.count += 1;
    }

    //
    // Returns `true` if deletion took place.
    // Otherwise, returns `false`
    //
    public boolean delete(E elem) {
        Node<E> prev_target = super.head;
        while (true) {
            Node<E> next = prev_target.getNext();
            if (next == null) { return false; }

            // 일치하는 원소를 찾음
            if (elem.compareTo(next.item) == 0) { break; }

            prev_target = next;
        }

        prev_target.removeNext();
        super.count -= 1;
        return true;
    }
}
