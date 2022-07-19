import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

public class Dijkstra {
    public static void main(String[] args) {
//        Note: Has different internal implementation from C++ version
//        Tested on CF Alpha Round 20 - C (https://codeforces.com/problemset/problem/20/C)
//        Status: AC (404ms - 15500 KB)
//        In general is quite slow, should probably use C++ in contest
    }

    static class DijkstraGraph {
        static class Edge implements Comparable<Edge> {
            long w;
            int u;
            Edge(long w, int u) {
                this.w = w;
                this.u = u;
            }
            @Override
            public int compareTo(Edge b) {
                return Long.compare(this.w, b.w);
            }
        }
        List<List<Edge>> adj;
        long[] dist;
        int[] prv;
        Queue<Edge> q;
        int s = -1;
        DijkstraGraph(int n) {
            adj = new ArrayList<>();
            dist = new long[n];
            prv = new int[n];
            q = new PriorityQueue<>();
            for (int i = 0; i < n; i++) {
                adj.add(new ArrayList<>());
            }
        }
        public void addEdge(int u, int v, long w) {
            adj.get(u).add(new Edge(w, v));
        }
        public void solve(int ns) {
            if (ns == s) {
                return;
            }
            s = ns;
            Arrays.fill(dist, Long.MAX_VALUE);
            dist[s] = 0;
            prv[s] = s;
            q.add(new Edge(0, s));
            while (!q.isEmpty()) {
                var e = q.poll();
                long d = e.w;
                int u = e.u;

                if (d > dist[u]) {
                    continue;
                }
                for (int i = 0; i < adj.get(u).size(); i++) {
                    int v = adj.get(u).get(i).u;
                    long w = adj.get(u).get(i).w;
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        prv[v] = u;
                        q.add(new Edge(dist[v], v));
                    }
                }
            }
        }
        public long getDistance(int u) { return dist[u]; }
        public int getPrv(int u) { return prv[u]; }
    }
}