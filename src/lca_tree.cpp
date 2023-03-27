#include <bits/stdc++.h>
using namespace std;

struct lca_tree {
    int n, lg;
    int clk = 0;
    vector<vector<int>> adj, parent;
    vector<int> in, out, h;
    lca_tree(int _n) {
        n = _n;
        lg = 32 - __builtin_clz(n);
        adj.assign(n, {});
        parent.assign(n, vector<int>(lg, -1));
        in.resize(n);
        out.resize(n);
        h.resize(n);
    }
    void add_edge(int u, int v) { adj[u].push_back(v); }

    void dfs(int u, int p) {
        in[u] = clk++;

        for (int i = 1; i < lg; i++) {
            if (parent[u][i - 1] != -1) {
                parent[u][i] = parent[parent[u][i - 1]][i - 1];
            }
        }

        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            h[v] = h[u] + 1;
            parent[v][0] = u;
            dfs(v, u);
        }

        out[u] = clk++;
    }
    void rooted_at(int root) { dfs(root, -1); }

    bool is_parent(int u, int v) { return in[v] >= in[u] & out[v] <= out[u]; }
    int lca(int u, int v) {
        if (is_parent(u, v))
            return u;
        if (is_parent(v, u))
            return v;

        for (int i = lg - 1; i >= 0; i--) {
            if (parent[u][i] != -1 && !is_parent(parent[u][i], v)) {
                u = parent[u][i];
            }
        }
        return parent[u][0];
    }
    int jump(int u, int k) {
        for (; k; k &= (k - 1)) {
            u = u == -1 ? u : parent[u][__builtin_ctz(k)];
        }
        return u;
    }
    int dist(int u, int v) { return h[u] + h[v] - 2 * h[lca(u, v)]; }
    int subtree_size(int u) { return (out[u] - in[u] + 1) / 2; }
};
