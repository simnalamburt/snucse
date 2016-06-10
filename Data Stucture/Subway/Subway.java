import java.io.*;
import java.util.*;

public class Subway {
    public static void main(String args[]) {
        if (args.length != 1) {
            System.err.println("\u001B[33m입력이 올바르게 주어지지 않음\u001B[0m");
            System.exit(1);
        }

        String filename = args[0];
        System.out.println(filename);
    }
}
