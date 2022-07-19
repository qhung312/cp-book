import java.util.Arrays;

public class DisjointSet {
    public static void main(String[] args) {
    }

    static class DSU {
        int[] f, sz, h;
        int n, maxSize = 1, numCC;
        DSU(int nn) {
            this.n = nn;
            numCC = n;
            f = new int[n];
            sz = new int[n];
            h = new int[n];
            Arrays.fill(sz, 1); Arrays.fill(h, 1);
            for (int i = 0; i < n; i++) {
                f[i] = i;
            }
        }
        public int parent(int u) {
            return u == f[u] ? u : (u = parent(f[u]));
        }
        public void join(int u, int v) {
            u = parent(u); v = parent(v);
            if (u == v) return;
            numCC--;
            if (h[u] < h[v]) {
                f[u] = v; sz[v] += sz[u];
            } else if (h[u] > h[v]) {
                f[v] = u; sz[u] += sz[v];
            } else {
                f[u] = v; sz[v] += sz[u]; h[v]++;
            }
            maxSize = Math.max(maxSize, sz[u]);
            maxSize = Math.max(maxSize, sz[v]);
        }
        public int getCCCount() { return numCC; }
        public int getMaxSize() { return maxSize; }
        public int sizeOf(int u) { return sz[parent(u)]; }
        public boolean same(int u, int v) { return parent(u) == parent(v); }
    }
}