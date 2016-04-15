import java.util.Iterator;
import java.util.NoSuchElementException;

//
// Homebrewed linked list
//
public class MyLinkedList<T> implements MyList<T> {
    // Dummy head
    final Node<T> head = new Node<T>(null);

    int count;

    @Override public boolean isEmpty() { return head.getNext() == null; }
    @Override public int size() { return count; }
    @Override public T first() { return head.getNext().item; }

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
    public void add(T item) {
        Node<T> last = head;
        while (last.getNext() != null) { last = last.getNext(); }

        last.insertNext(item);
        count += 1;
    }

    @Override
    public void removeAll() {
        while (head.getNext() != null) { head.removeNext(); }
    }
}

//
// MyLinkedList의 노드가 될 객체
//
class Node<T> {
    public final T item;
    private Node<T> next;

    // 새 Node<T>를 만든다.
    public Node(T obj) {
        this.item = obj;
        this.next = null;
    }

    public Node<T> getNext() { return next; }

    // T obj로 새 Node<T>를 만들어, this의 next 자리에 끼워넣는다.
    public void insertNext(T obj) {
        Node<T> new_next = new Node<T>(obj);
        if (this.next == null) { this.next = new_next; return; }

        Node<T> old_next = this.next;

        // Before: this  ------------------->  old_next
        //
        // After:  this  ---> new_next  ---->  old_next

        this.next = new_next;
        new_next.next = old_next;
    }

    // this다음에 있는 노드를 링크드리스트에서 제거한다.
    public void removeNext() {
        if (this.next == null) { throw new NoSuchElementException(); }

        // Before: this ---> this.next ---> new_next
        //
        // After:  this ------------------> new_next
        //                   this.next ---> new_next

        this.next = this.next.next;
    }
}

class MyLinkedListIterator<T> implements Iterator<T> {
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
        list.count -= 1;
        curr = prev;
        prev = null;
    }
}
