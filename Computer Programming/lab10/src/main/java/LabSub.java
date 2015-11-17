/**
 * Created by 301-412 on 2015-11-17.
 */
public class LabSub {
    public static int mNumber = 0;
    public int a;

    public LabSub(int b) {
        a = b;
        mNumber++;
    }

    public String toString() {
        return "Value holding is " + a;
    }
}
