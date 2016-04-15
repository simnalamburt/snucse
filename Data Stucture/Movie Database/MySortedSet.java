public class MySortedSet<E extends Comparable<E>> extends MyLinkedList<E> {
    @Override
    public void add(E elem) {
        Node<E> target = head;
        while (true) {
            Node<E> next = target.getNext();
            if (next == null) { break; }

            int ret = elem.compareTo(next.item);
            if (ret == 0) { return; }
            if (ret < 0) { break; }

            target = next;
        }

        target.insertNext(elem);
        super.numItems += 1;
    }
}
