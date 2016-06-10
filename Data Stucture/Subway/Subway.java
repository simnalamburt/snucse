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
    public static void main(String args[]) {
        if (args.length != 1) {
            System.err.println("\u001B[33m입력이 올바르게 주어지지 않았습니다.\u001B[0m");
            System.exit(1);
        }

        final Path path = Paths.get(args[0]);
        try {
            parse_data(path);
        } catch(IOException e) {
            System.err.printf("\u001B[33m파일 \u001B[31m%s\u001B[33m를 읽던중 에러가 발생하였습니다.\u001B[0m", path);
            System.exit(1);
            return;
        }
    }

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
}
