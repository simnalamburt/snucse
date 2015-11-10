public class Main {
  public static void main(String[] argv) {
    int pointers[][] = new int[6][2];
    pointers[0][0] = 1;
    pointers[0][1] = 1;
    pointers[1][0] = 4;
    pointers[1][1] = 6;
    pointers[2][0] = 9;
    pointers[2][1] = 7;
    pointers[3][0] = 2;
    pointers[3][1] = 3;
    pointers[4][0] = 4;
    pointers[4][1] = 9;
    pointers[5][0] = 8;
    pointers[5][1] = 8;

    int min = Integer.MAX_VALUE;
    int A = 0, B = 0;
    for (int a = 0; a < 6; ++a) {
      for (int b = a + 1; b < 6; ++b) {
        if (pointers[a][0] == 0 ||
            pointers[b][0] == 0 ||
            pointers[a][1] == 0 ||
            pointers[b][1] == 0)
        {
          continue;
        }

        int dx = pointers[a][0] - pointers[b][0];
        int dy = pointers[a][1] - pointers[b][1];

        int distsquare = dx*dx + dy*dy;
        if (min > distsquare) {
          min = distsquare;
          A = a;
          B = b;
        }
      }
    }

    System.out.format("P%d ~ P%d : %f\n", A, B, Math.sqrt((double)min));
  }
}
