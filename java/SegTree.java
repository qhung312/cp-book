import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.function.BiFunction;

public class SegTree {
    public static void main(String[] args) {
    }

    static class Info {
    }

    static class SegmentTree<T> {
        private int n;
        private T[] st;
        BiFunction<T, T, T> merge;
        SegmentTree(int nn, BiFunction<T, T, T> f) {
            n = nn;
            st = (T[]) new Object[4 * n + 100];
            merge = f;
        }
        private void merge(int p) {
            st[p] = merge.apply(st[2 * p], st[2 * p + 1]);
        }
        private void modify(int p, int l, int r, int i, T x) {
            if (i > r || i < l) {
                return;
            }
            if (l == r) {
                st[p] = x;
                return;
            }
            int m = (l + r) / 2;
            modify(2 * p, l, m, i, x);
            modify(2 * p + 1, m + 1, r, i, x);
            merge(p);
        }
        public void modify(int i, T x) {
            modify(1, 0, n - 1, i, x);
        }
        private T query(int p, int l, int r, int i, int j) {
            if (r < i || l > j) return null;
            if (l >= i && r <= j) return st[p];
            int m = (l + r) / 2;
            T ln = query(2 * p, l, m, i, j);
            T rn = query(2 * p + 1, m + 1, r, i, j);
            return merge.apply(ln, rn);
        }
        public T query(int l, int r) {
            return query(1, 0, n - 1, l, r);
        }
    }
}