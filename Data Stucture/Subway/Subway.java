import java.io.*;
import java.util.*;
import java.nio.file.*;
import static java.nio.charset.Charset.forName;

class Station {
    final String name;
    final ArrayList<Edge> neighbors;

    Station(String name) {
        this.name = name;
        this.neighbors = new ArrayList<Edge>();
    }

    @Override
    public String toString() { return name; }
}

class Edge {
    final Station dest;
    final String kind;
    final long weight;

    Edge(Station dest, String kind, long weight) {
        this.dest = dest;
        this.kind = kind;
        this.weight = weight;
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
        final BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
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

            System.out.print(find_path(db.values(), from, to));
        }
    }

    //
    // Parse input data
    //
    static HashMap<String, Station> parse_data(Path path) throws IOException {
        final HashMap<String, Station> db = new HashMap<String, Station>();

        // Cache which stores side information
        class CacheEntry { Station station; String kind; }
        final HashMap<String, CacheEntry> cache = new HashMap<String, CacheEntry>();

        final List<String> lines = Files.readAllLines(path, forName("UTF-8"));
        final Iterator<String> iter = lines.iterator();
        while (iter.hasNext()) {
            final String line = iter.next();
            if ("".equals(line)) { break; }

            // Parse
            final String[] params = line.split(" ");
            if (params.length != 3) { throw new IOException(); }

            String id   = params[0],
                   name = params[1],
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

            CacheEntry from = cache.get(params[0]),
                       to   = cache.get(params[1]);
            long weight  = Long.parseLong(params[2]);
            if (!from.kind.equals(to.kind)) { throw new IOException(); }

            // Connect stations
            from.station.neighbors.add(new Edge(to.station, to.kind, weight));
        }

        return db;
    }

    //
    // Find shortest path
    //
    static String find_path(Collection<Station> stations, final Station start, Station dest) {
        class Entry implements Comparable<Entry> {
            long cost;
            ArrayList<Edge> path;

            Entry() {
                this.cost = 0;
                this.path = new ArrayList<Edge>();
            }

            private Entry(Entry other) {
                this.cost = other.cost;
                this.path = new ArrayList<Edge>(other.path);
            }

            @Override
            public int compareTo(Entry other) {
                return Long.compare(this.cost, other.cost);
            }

            Station last() {
                return path.size() == 0
                    ? start
                    : path.get(path.size() - 1).dest;
            }

            Entry extend(Edge edge) {
                // TODO: Copy-on-write
                Entry ret = new Entry(this);

                // 환승
                if (path.size() != 0 && !path.get(path.size() - 1).kind.equals(edge.kind)) { ret.cost += 5; }
                ret.cost += edge.weight;
                ret.path.add(edge);
                return ret;
            }
        }

        final PriorityQueue<Entry> shortest = new PriorityQueue<Entry>();
        final HashSet<Station> unvisited = new HashSet<Station>(stations);

        // Insert initial task
        shortest.add(new Entry());
        unvisited.remove(start);

        // Iteration
        Entry entry;
        while ((entry = shortest.poll()) != null) {
            Station last = entry.last();
            if (last == dest) { break; }

            for (Edge neighbor : last.neighbors) {
                if (!unvisited.contains(neighbor.dest)) { continue; }

                // Insert new task
                shortest.add(entry.extend(neighbor));
                unvisited.remove(neighbor.dest);
            }
        }

        StringBuilder buf = new StringBuilder();
        buf.append(start);
        for (ListIterator<Edge> iter = entry.path.listIterator(); iter.hasNext(); ) {
            Edge edge = iter.next();

            // Detect if transfer occurs
            final boolean transfer = iter.hasNext()
                && !edge.kind.equals(entry.path.get(iter.nextIndex()).kind);

            buf.append(' ');
            if (transfer) {
                buf.append('[');
                buf.append(edge.dest);
                buf.append(']');
            } else {
                buf.append(edge.dest);
            }
        }
        buf.append('\n');
        buf.append(entry.cost);
        buf.append('\n');
        return buf.toString();
    }
}
