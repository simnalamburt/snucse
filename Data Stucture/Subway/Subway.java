import java.io.*;
import java.util.*;
import java.nio.file.*;
import static java.nio.charset.Charset.forName;

class Station {
    final String name;
    final PriorityQueue<Edge> neighbors;

    Station(String name) {
        this.name = name;
        this.neighbors = new PriorityQueue<Edge>();
    }

    @Override
    public String toString() { return name; }
}

class Edge implements Comparable<Edge> {
    final Station dest;
    final String kind;
    final int weight;

    Edge(Station dest, String kind, int weight) {
        this.dest = dest;
        this.kind = kind;
        this.weight = weight;
    }

    @Override
    public int compareTo(Edge other) {
        return Integer.compare(this.weight, other.weight);
    }

    @Override
    public String toString() { return "->" + dest + " (" + weight + ')'; }
}

public class Subway {
    //
    // Entry point
    //
    public static void main(String args[]) {
        if (args.length != 1) {
            System.err.println("\u001B[33m입력이 올바르게 주어지지 않았습니다.\u001B[0m");
            System.exit(1);
        }

        // Parse args[0]
        final HashMap<String, Station> db;
        final Path path = Paths.get(args[0]);
        try {
            db = parse_data(path);
        } catch(IOException e) {
            System.err.printf("\u001B[33m파일 \u001B[31m%s\u001B[33m를 읽던중 에러가 발생하였습니다.\u001B[0m\n", path);
            System.exit(1);
            return;
        }

        // Parse stdin
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            final String line;
            try {
                line = stdin.readLine();
            } catch(IOException e) {
                System.err.print("\u001B[31mstdin\u001B[33m을 읽던중 에러가 발생하였습니다.\u001B[0m\n");
                System.exit(1);
                return;
            }
            if (line == null) { break; }
            if (line.equals("QUIT")) { break; }

            final String[] params = line.split(" ");
            if (params.length != 2) {
                System.err.print("\u001B[31mstdin\u001B[33m의 형식이 잘못되었습니다.\u001B[0m\n");
                continue;
            }

            final Station from = db.get(params[0]), to = db.get(params[1]);

            final String err;
            if (from == null) { err = params[0]; }
            else if (to == null) { err = params[1]; }
            else { err = null; }
            if (err != null) {
                System.err.printf("\u001B[31m%s\u001B[33m는 없는 지하철역입니다.\u001B[0m\n", err);
                continue;
            }

            find_path(from, to);
        }
    }

    //
    // Parse input data
    //
    static HashMap<String, Station> parse_data(Path path) throws IOException {
        final HashMap<String, Station> db = new HashMap<String, Station>();

        // Cache which stores side information
        class CacheEntry { Station station; String kind; }
        final HashMap<Integer, CacheEntry> cache = new HashMap<Integer, CacheEntry>();

        final List<String> lines = Files.readAllLines(path, forName("UTF-8"));
        final Iterator<String> iter = lines.iterator();
        while (iter.hasNext()) {
            final String line = iter.next();
            if ("".equals(line)) { break; }

            // Parse
            final String[] params = line.split(" ");
            if (params.length != 3) { throw new IOException(); }

            int id = Integer.parseInt(params[0]);
            String  name = params[1],
                    kind = params[2];

            // Lookup for the station with same name
            Station station = db.get(name);
            if (station == null) {
                // New station
                station = new Station(name);
                db.put(name, station);
            }

            // Store side information
            CacheEntry entry = new CacheEntry();
            entry.station = station;
            entry.kind = kind;
            cache.put(id, entry);
        }

        while (iter.hasNext()) {
            // Parse
            final String[] params = iter.next().split(" ");
            if (params.length != 3) { throw new IOException(); }

            CacheEntry  from    = cache.get(Integer.parseInt(params[0])),
                        to      = cache.get(Integer.parseInt(params[1]));
            int weight  = Integer.parseInt(params[2]);
            if (!from.kind.equals(to.kind)) { throw new IOException(); }

            // Connect stations
            from.station.neighbors.add(new Edge(to.station, to.kind, weight));
        }

        return db;
    }

    //
    // Find shortest path
    //
    static void find_path(Station start, Station dest) {
        System.out.printf("%s -> %s\n", start, dest);

        // TODO
    }
}
