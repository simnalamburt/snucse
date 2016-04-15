import java.util.Iterator;
import java.util.NoSuchElementException;

//
// Genre, Title 을 관리하는 영화 데이터베이스.
//
// MyLinkedList 를 사용해 각각 Genre와 Title에 따라 내부적으로 정렬된 상태를
// 유지하는 데이터베이스이다.
//
public class MovieDB {
    private final MySortedSet<MovieDBItem> set = new MySortedSet<MovieDBItem>();

    public void insert(MovieDBItem item) {
        // TODO: Remove debug codes
        System.err.printf("[trace] MovieDB: INSERT [%s] [%s]\n", item.genre, item.title);

        set.add(item);
    }

    public void delete(MovieDBItem item) {
        // TODO: Remove debug codes
        System.err.printf("[trace] MovieDB: DELETE [%s] [%s]\n", item.genre, item.title);

        set.delete(item);
    }

    public MyLinkedList<MovieDBItem> search(String term) {
        // TODO: Remove debug codes
        System.err.printf("[trace] MovieDB: SEARCH [%s]\n", term);

        MyLinkedList<MovieDBItem> result = new MyLinkedList<MovieDBItem>();
        for (MovieDBItem item : set) {
            if (item.title.contains(term)) { result.add(item); }
        }
        return result;
    }

    public MyLinkedList<MovieDBItem> items() {
        // TODO: Remove debug codes
        System.err.printf("[trace] MovieDB: ITEMS\n");

        return set;
    }
}

// TODO: 이 타입이 필요한가?
class Genre extends Node<String> implements Comparable<Genre> {
    public Genre(String name) {
        super(name);
        throw new UnsupportedOperationException("not implemented yet");
    }

    @Override
    public int compareTo(Genre o) {
        throw new UnsupportedOperationException("not implemented yet");
    }

    @Override
    public int hashCode() {
        throw new UnsupportedOperationException("not implemented yet");
    }

    @Override
    public boolean equals(Object obj) {
        throw new UnsupportedOperationException("not implemented yet");
    }
}

// TODO: 이 타입이 필요한가?
class MovieList extends MySortedSet<String> { }
