// 2013-11392 김지현

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class FinalDriver {
    public static void main(String[] args) {
        tree(args[0],args[1]);
        tensor(args[2],args[3]);
    }

    public static void tensor(String fin, String fout) {
        String input = readfile(fin);

        String[] lines = input.split("\n");

        int count = Integer.parseInt(lines[0]);

        Tensor[] nums = new Tensor[count + 1];
        for (int i = 1; i <= count; ++i) {
            String line = lines[i];
            String[] tokens = line.split(" ");

            switch(tokens[0]) {
                case "S":
                    nums[i] = new MyScalar(Integer.parseInt(tokens[1]));
                    break;
                case "V":
                    int size = Integer.parseInt(tokens[1]);
                    int[] list = new int[size];
                    for (int x = 0; x < size; ++x) {
                        list[x] = Integer.parseInt(tokens[2 + x]);
                    }
                    nums[i] = new MyVector(list);
                    break;
                case "M":
                    int row = Integer.parseInt(tokens[1]);
                    int col = Integer.parseInt(tokens[2]);
                    int[][] mat = new int[row][col];
                    for (int y = 0; y < row; ++y) {
                        for (int x = 0; x < col; ++x) {
                            mat[y][x] = Integer.parseInt(tokens[3 + y*col + x]);
                        }
                    }
                    nums[i] = new MyMatrix(mat);
                    break;
            }
        }

        StringBuffer result = new StringBuffer();

        for (int i = 1; i <= count; ++i) {
            result.append(nums[i]);
            result.append('\n');
        }

        for (int i = count + 1; i < lines.length; ++i) {
            String line = lines[i];
            String[] tokens = line.split(" ");

            Tensor left = nums[Integer.parseInt(tokens[0])];
            String op = tokens[1];
            Tensor right = nums[Integer.parseInt(tokens[2])];

            Tensor ret;
            switch (op) {
                case "+":
                    result.append(left.add(right));
                    break;
                case "*":
                    result.append(left.multiply(right));
                    break;
                case "p=":
                    MyVector v1 = (MyVector)left;
                    MyVector v2 = (MyVector)right;
                    result.append(v1.permuteCompare(v2) ? "True" : "False");
            }
            result.append('\n');
        }

        writefile(fout, result.toString());
    }

    public static void tree(String input, String output) {
        String[] line = readfile(input).split("\n");
        BinSearchTree tree = new BinSearchTree();
        String searchresult = "";
        for(int i = 0; i < line.length; i++) {
            String[] word = line[i].trim().split(" ");
            if(word[0].compareTo("ADD") == 0)
                tree.insert(Integer.parseInt(word[1]));
            else if(word[0].compareTo("DELETE") == 0)
                tree.delete(Integer.parseInt(word[1]));
            else if(word[0].compareTo("SEARCH") == 0) {
                searchresult += word[1] + ": " + tree.search(Integer.parseInt(word[1])) + "\n";
            }

        }
        writefile(output, searchresult + tree.toString());
    }

    public static String readfile(String file) {
        String everything = "";
        try {
            BufferedReader br = new BufferedReader(new FileReader(file));
            StringBuilder sb = new StringBuilder();
            String line = br.readLine();

            while (line != null) {
                sb.append(line);
                sb.append(System.lineSeparator());
                line = br.readLine();
            }
            everything = sb.toString();
            br.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
        return everything;
    }

    public static void writefile(String file, String everything) {
        try {
            PrintWriter writer = new PrintWriter(file);
            writer.print(everything);
            writer.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
}
