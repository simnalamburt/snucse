import java.util.Iterator;
import java.util.NoSuchElementException;

public class AssignmentGuide {
    /*
     * This program tests the basic functionality of your MyLinkedList. You can start your assignment here.
     * DISCLAIMER: Passing basic tests given here DOES NOT NECESSARILY GUARANTEES that your assignment is correct.
     *
     * When you run this program for the first time, it will print a lot of lines of error messages.
     * DON'T PANIC and read those messages. They will provide you some hints in how to implement your assignment.
     *
     * Make this program print "All test passed!" instead of error messages.
     *
     */
    public static void main(String[] args) {
        // You should skip the details of this testAssert method.
        // Implementation of this method is provided at the bottom of this file.
        testAssert();

        try {
            testLinkedList();
            testSortedSet();

            System.out.println("All test passed! You can move on to MovieDatabaseConsole!");

        } catch (Throwable t) {
            t.printStackTrace(System.err);
            System.err.println("Test failed! Debug your program with the information above");
        }
    }

    private static void testLinkedList() {
        MyList<String> l = new MyLinkedList<>();

        // You should not modify these lines below to pass the tests.
        String item1 = "Data Structure";
        l.add(item1);
        assert l.size() == 1 : SIZE_FAILURE_MSG(l.size(), 1);;
        assert l.first().equals(item1) : VALUE_FAILURE_MSG("l.first()", l.first(), item1);

        String item2 = "System Programming";
        l.add(item2);
        assert l.size() == 2 : SIZE_FAILURE_MSG(l.size(), 2);
        assert l.first().equals(item1) : VALUE_FAILURE_MSG("l.first()", l.first(), item1);

        String item3 = "Computer Architecture";
        l.add(item3);
        assert l.size() == 3 : SIZE_FAILURE_MSG(l.size(), 3);
        assert l.first().equals(item1) : VALUE_FAILURE_MSG("l.first()", l.first(), item3);

        Iterator<String> it = l.iterator();
        String next = null;

        assert it.hasNext() : "it.hasNext() should return true at this line.";
        next = it.next();
        assert next.equals(item1) : VALUE_FAILURE_MSG("it.next()", next, item3);

        assert it.hasNext() : "it.hasNext() should return true at this line.";
        next = it.next();
        assert next.equals(item2) : VALUE_FAILURE_MSG("it.next()", next, item1);

        assert it.hasNext() : "it.hasNext() should return true at this line.";
        next = it.next();
        assert next.equals(item3) : VALUE_FAILURE_MSG("it.next()", next, item2);

        assert it.hasNext() == false : "it.hasNext() should return false at this line.";

        it = l.iterator();
        it.next();
        it.remove();
        assert l.size() == 2 : SIZE_FAILURE_MSG(l.size(), 2);
        try {
            it.remove();
            assert false : "should not reach here";
        } catch (IllegalStateException e) {
            // expected
        }
        it.next();
        it.remove();
        assert l.size() == 1 : SIZE_FAILURE_MSG(l.size(), 1);
        it.next();
        it.remove();
        assert l.size() == 0 : SIZE_FAILURE_MSG(l.size(), 0);;
        try {
            it.next();
            assert false : "should not reach here";
        } catch (NoSuchElementException e) {
            // expected
        }
    }

    private static void testSortedSet() {
        MyList<String> l = new MySortedSet<String>();

        // You should not modify these lines below to pass the tests.
        String item1 = "Data Structure";
        l.add(item1);
        assert l.size() == 1 : SIZE_FAILURE_MSG(l.size(), 1);;
        assert l.first().equals(item1) : VALUE_FAILURE_MSG("l.first()", l.first(), item1);

        String item2 = "System Programming";
        l.add(item2);
        assert l.size() == 2 : SIZE_FAILURE_MSG(l.size(), 2);
        assert l.first().equals(item1) : VALUE_FAILURE_MSG("l.first()", l.first(), item1);

        String item3 = "Computer Architecture";
        l.add(item3);
        assert l.size() == 3 : SIZE_FAILURE_MSG(l.size(), 3);
        assert l.first().equals(item3) : VALUE_FAILURE_MSG("l.first()", l.first(), item3);

        l.add(item1);
        assert l.size() == 3 : SIZE_FAILURE_MSG(l.size(), 3);

        Iterator<String> it = l.iterator();
        String next = null;

        assert it.hasNext() : "it.hasNext() should return true at this line.";
        next = it.next();
        assert next.equals(item3) : VALUE_FAILURE_MSG("it.next()", next, item3);

        assert it.hasNext() : "it.hasNext() should return true at this line.";
        next = it.next();
        assert next.equals(item1) : VALUE_FAILURE_MSG("it.next()", next, item1);

        assert it.hasNext() : "it.hasNext() should return true at this line.";
        next = it.next();
        assert next.equals(item2) : VALUE_FAILURE_MSG("it.next()", next, item2);

        assert it.hasNext() == false : "it.hasNext() should return false at this line.";
    }


    private static String VALUE_FAILURE_MSG(String target, String value, String expected) {
        return String.format("expected %s is [%s] but [%s]", target, expected, value);
    }

    private static String SIZE_FAILURE_MSG(int value, int expected) {
        return String.format("l.size() should be %d but %d", expected, value);
    }

    private static void testAssert() {
        try {
            assert false;
        } catch (Throwable t) {
            return;
        }

        System.err.println("You should run this program with assert switch. Try \"java -ea AssignmentGuide\".");
        System.err.println("If you're using Eclipse, add \"-ea\" switch in Run/Debug Configurations - Arguments - VM arguments.");
        System.exit(1);
    }
}
