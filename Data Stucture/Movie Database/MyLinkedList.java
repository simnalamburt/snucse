import java.util.Iterator;
import java.util.NoSuchElementException;

public class MyLinkedList<T> implements MyList<T> {
    // dummy head
    final Node<T> head = new Node<T>(null);
    int numItems;

    //
    // iterator() 메소드를 제공하는 클래스의 인스턴스는 다음과 같은 자바
    // for-each 문법의 혜택을 볼 수 있다.
    //
    // ```java
    // for (T item: iterable) {
    // 	item.someMethod();
    // }
    // ```
    //
    // ###### Reference
    // - PrintCmd#apply (ConsoleCommand.java)
    // - SearchCmd#apply (ConsoleCommand.java)
    // - java.lang.Iterable#iterator
    //
    @Override
    public final Iterator<T> iterator() {
        return new MyLinkedListIterator<T>(this);
    }

    @Override
    public boolean isEmpty() {
        return head.getNext() == null;
    }

    @Override
    public int size() {
        return numItems;
    }

    @Override
    public T first() {
        return head.getNext().item;
    }

    @Override
    public void add(T item) {
        Node<T> last = head;
        while (last.getNext() != null) { last = last.getNext(); }

        last.insertNext(item);
        numItems += 1;
    }

    @Override
    public void removeAll() {
        while (head.getNext() != null) { head.removeNext(); }
    }
}

class MyLinkedListIterator<T> implements Iterator<T> {
    // Implement the iterator for MyLinkedList.
    // You have to maintain the current position of the iterator.
    private final MyLinkedList<T> list;
    private Node<T> curr, prev;

    public MyLinkedListIterator(MyLinkedList<T> list) {
        this.list = list;
        this.curr = list.head;
        this.prev = null;
    }

    @Override
    public boolean hasNext() { return curr.getNext() != null; }

    @Override
    public T next() {
        if (!hasNext()) { throw new NoSuchElementException(); }

        prev = curr;
        curr = curr.getNext();
        return curr.item;
    }

    @Override
    public void remove() {
        if (prev == null) { throw new IllegalStateException("next() should be called first"); }
        if (curr == null) { throw new NoSuchElementException(); }

        prev.removeNext();
        list.numItems -= 1;
        curr = prev;
        prev = null;
    }
}
