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

    public void insert(MovieDBItem item) { set.add(item); }
    public void delete(MovieDBItem item) { set.delete(item); }
    public MyLinkedList<MovieDBItem> items() { return set; }

    public MyLinkedList<MovieDBItem> search(String term) {
        MyLinkedList<MovieDBItem> result = new MyLinkedList<MovieDBItem>();
        for (MovieDBItem item : set) {
            if (item.title.contains(term)) { result.add(item); }
        }
        return result;
    }
}
