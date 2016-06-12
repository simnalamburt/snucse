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
    final long weight;

    Edge(Station dest, long weight) {
        this.dest = dest;
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
        final HashMap<String, ArrayList<Station>> db;
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
            } catch(IllegalArgumentException e) {
                System.err.println("\u001B[33m입력파일 형식이 스펙과 맞지 않습니다.\u001B[0m");
                continue;
            } catch(IOException e) {
                System.err.println("\u001B[31mstdin\u001B[33m을 읽던중 에러가 발생하였습니다.\u001B[0m");
                System.exit(1);
                return;
            }
            if (line == null) { break; }
            if (line.equals("QUIT")) { break; }

            final Params params;
            try {
                params = Params.parse_input(line);
            } catch(IllegalArgumentException e) {
                final String msg = e.getMessage();
                if (msg == null) {
                    System.err.print("\u001B[33m");
                    System.err.print(msg);
                    System.err.println("\u001B[0m");
                } else {
                    System.err.println("\u001B[31mstdin\u001B[33m의 형식이 잘못되었습니다.\u001B[0m");
                }
                continue;
            }

            final String result;
            try {
                result = find_path(db, params);
            } catch(IllegalArgumentException e) {
                final String msg = e.getMessage();
                System.err.print("\u001B[33m");
                System.err.print(msg != null ? msg : "최단경로 계산도중 에러가 발생하였습니다.");
                System.err.println("\u001B[0m");
                continue;
            }

            System.out.print(result);
        }
    }

    //
    // Parse input data
    //
    static HashMap<String, ArrayList<Station>> parse_data(Path path) throws IOException {
        final HashMap<String, ArrayList<Station>> db = new HashMap<String, ArrayList<Station>>();
        final HashMap<String, Station> id_station_map = new HashMap<String, Station>();

        final List<String> lines = Files.readAllLines(path, forName("UTF-8"));
        final Iterator<String> iter = lines.iterator();
        while (iter.hasNext()) {
            final String line = iter.next();
            if ("".equals(line)) { break; }

            // Parse
            final String[] params = line.split(" ");
            if (params.length < 2) { throw new IllegalArgumentException(); }

            final String id   = params[0],
                         name = params[1];

            // Create new station
            Station station = new Station(name);

            // Insert it into DB
            ArrayList<Station> entry = db.get(name);
            if (entry == null) {
                entry = new ArrayList<Station>();
                db.put(name, entry);
            }
            entry.add(station);

            // Store side information
            id_station_map.put(id, station);
        }

        while (iter.hasNext()) {
            // Parse
            final String[] params = iter.next().split(" ");
            if (params.length != 3) { throw new IllegalArgumentException(); }

            final Station from = id_station_map.get(params[0]),
                          to   = id_station_map.get(params[1]);
            final long weight  = Long.parseLong(params[2]);

            // Connect stations
            from.neighbors.add(new Edge(to, weight));
        }

        // Connect the stations with a same name
        for (final ArrayList<Station> stations : db.values()) {
            assert stations.size() > 0;
            if (stations.size() == 1) { continue; }

            final int size = stations.size();
            for (int i = 0; i < size - 1; ++i) {
                for (int j = i + 1; j < size; ++j) {
                    final Station lhs = stations.get(i),
                                  rhs = stations.get(j);

                    final long weight = 5;
                    lhs.neighbors.add(new Edge(rhs, weight));
                    rhs.neighbors.add(new Edge(lhs, weight));
                }
            }
        }

        return db;
    }

    //
    // Find shortest path
    //
    static String find_path(HashMap<String, ArrayList<Station>> db, final Params params) {
        final ArrayList<Station> src_stations = db.get(params.from);
        final ArrayList<Station> dst_stations = db.get(params.to);
        if (src_stations == null) { throw new IllegalArgumentException('\'' + params.from + "'는 없는 지하철역입니다."); }
        if (dst_stations == null) { throw new IllegalArgumentException('\'' + params.to + "'는 없는 지하철역입니다."); }
        assert src_stations.size() > 0;
        assert dst_stations.size() > 0;

        class Entry implements Comparable<Entry> {
            long transfer, time;
            ArrayList<Station> path;

            Entry(Station start) {
                this.transfer = 0;
                this.time = 0;
                this.path = new ArrayList<Station>();
                this.path.add(start);
            }

            private Entry(Entry other) {
                this.transfer = other.transfer;
                this.time = other.time;
                this.path = new ArrayList<Station>(other.path);
            }

            @Override
            public int compareTo(Entry other) {
                if (params.type == Params.Type.MinimumTransfer) {
                    int ret = Long.compare(this.transfer, other.transfer);
                    if (ret != 0) { return ret; }
                }
                return Long.compare(this.time, other.time);
            }

            Station last() {
                assert path.size() > 0;
                return path.get(path.size() - 1);
            }

            Entry extend(Edge edge) {
                // TODO: Copy-on-write
                Entry ret = new Entry(this);
                if (this.last().name.equals(edge.dest.name)) { ret.transfer += 1; }
                ret.time += edge.weight;
                ret.path.add(edge.dest);
                return ret;
            }
        }

        final PriorityQueue<Entry> dijkstra = new PriorityQueue<Entry>();
        final HashSet<Station> undecided = new HashSet<Station>();
        final HashSet<Station> destination = new HashSet<Station>(dst_stations);

        // Initialize
        for (ArrayList<Station> stations : db.values()) {
            for (final Station station : stations) { undecided.add(station); }
        }

        // Insert initial tasks
        for (final Station start : src_stations) { dijkstra.add(new Entry(start)); }

        // Perform dijkstra algorithm
        Entry entry;
        while ((entry = dijkstra.poll()) != null) {
            Station current = entry.last();
            if (destination.contains(current)) { break; }
            if (!undecided.contains(current)) { continue; }
            undecided.remove(current);

            for (Edge neighbor : current.neighbors) {
                if (!undecided.contains(neighbor.dest)) { continue; }

                // Insert new task
                dijkstra.add(entry.extend(neighbor));
            }
        }

        if (entry == null) {
            throw new IllegalArgumentException('\'' + params.from + "'에서 '" + params.to + "'로 갈 수 있는 길이 없습니다.");
        }
        assert entry.path != null;
        assert entry.path.size() > 0;

        // Dedup station names and check if transfer occured
        class Result {
            String name; boolean transfer = false;
            Result(String name) { this.name = name; }
            @Override public String toString() { return transfer ? '['+name+']' : name; }
        };
        final ArrayList<Result> results = new ArrayList<Result>();

        final Iterator<Station> iter = entry.path.iterator();
        {
            final Station station = iter.next();
            results.add(new Result(station.name));
        }
        while (iter.hasNext()) {
            final Station station = iter.next();

            Result last = results.get(results.size() - 1);
            if (last != null && last.name.equals(station.name)) {
                last.transfer = true;
            } else {
                results.add(new Result(station.name));
            }
        }
        assert results.size() > 0;

        // Pretty print result
        StringBuilder buf = new StringBuilder();
        final Iterator<Result> it = results.iterator();
        buf.append(it.next());
        while (it.hasNext()) {
            buf.append(' ');
            buf.append(it.next());
        }
        buf.append('\n');
        buf.append(entry.time);
        buf.append('\n');
        return buf.toString();
    }
}

class Params {
    static enum Type { MinimumTime, MinimumTransfer };

    public final String from;
    public final String to;
    public final Type type;

    private Params(String from, String to, Type type) {
        this.from = from;
        this.to   = to;
        this.type = type;
    }

    static Params parse_input(String line) {
        final String[] params = line.split(" ");
        if (params.length < 2) { throw new IllegalArgumentException("도착지를 입력해주세요."); }

        final Type type = params.length < 3 ? Type.MinimumTime : Type.MinimumTransfer;
        if (type == Type.MinimumTransfer && !"!".equals(params[2])) {
            throw new IllegalArgumentException("세번째 인자는 '!' 외의 글자는 허용되지 않습니다.");
        }

        return new Params(params[0], params[1], type);
    }
}
