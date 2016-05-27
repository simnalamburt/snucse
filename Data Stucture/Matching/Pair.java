public class Pair<T1, T2> {
    public T1 first;
    public T2 second;

    public static <T1, T2> Pair<T1, T2> of(T1 fst, T2 snd) {
        Pair<T1, T2> ret = new Pair<T1, T2>();
        ret.first = fst;
        ret.second = snd;
        return ret;
    }

    @Override
    public String toString() { return "(" + first + ", " + second + ")"; }
}
