import java.util.Objects;

//
// Java 1.7에 호환되도록 구현한 모나딕 Option 타입
//
// Reference:
//   https://docs.oracle.com/javase/8/docs/api/java/util/Optional.html
//
public final class Option<T> {
    private final T data;
    private Option() { data = null; }
    private Option(T data) { this.data = Objects.requireNonNull(data); }

    private static final Option<?> EMPTY = new Option<>();
    public static <E> Option<E> empty() {
        @SuppressWarnings("unchecked")
        Option<E> t = (Option<E>) EMPTY;
        return t;
    }
    public static <E> Option<E> of(E data) {
        return new Option<E>(data);
    }
    public static <E> Option<E> ofNullable(E value) {
        return value == null ? Option.<E>empty() : of(value);
    }

    public boolean isPresent() { return data != null; }

    public T orElse(T other) { return data != null ? data : other; }

    public Option<T> filter(Predicate<? super T> predicate) {
        Objects.requireNonNull(predicate);
        if (!isPresent()) { return this; }
        return predicate.test(data) ? this : Option.<T>empty();
    }

    public <E> Option<E> map(Function<? super T, ? extends E> mapper) {
        Objects.requireNonNull(mapper);
        if (!isPresent()) { return empty(); }
        return Option.ofNullable(mapper.apply(data));
    }

    public <E> Option<E> flatMap(Function<? super T, Option<E>> mapper) {
        Objects.requireNonNull(mapper);
        if (!isPresent()) { return empty(); }
        return Objects.requireNonNull(mapper.apply(data));
    }
}
