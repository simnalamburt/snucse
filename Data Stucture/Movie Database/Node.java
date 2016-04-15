import java.util.NoSuchElementException;

// TODO: MyLinkedList 안으로 넣기
public class Node<T> {
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
