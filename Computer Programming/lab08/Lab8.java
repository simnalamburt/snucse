import java.util.Random;

public class Lab8 {
  public static void main(String[] argv) {
    int count = 0;
    Random rng = new Random();

    while (true) {
      int left = rng.nextInt(12) + 1;
      int right = rng.nextInt(12) + 1;
      count += 1;

      System.out.format("%d %d\n", left, right);

      if (left == 12 && right == 12) { break; }
    }

    System.out.format("\nWe rolled dices %d times\n", count);
  }
}
