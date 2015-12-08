import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

public class FinalDriver {
    public static void main(String[] args) {
        tree(args[0],args[1]);
        tensor(args[2],args[3]);
    }

    public static void tensor(String input, String output) {
        /**
         * String input = input file name
         * String output = output file name
         */
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
