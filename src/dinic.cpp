#include <bits/stdc++.h>
using namespace std;

// Copied from: jiangly

template<class T>
struct dinic {
    const int n;
    struct Edge {
        int to;
        T cap;
        Edge(int to, T cap) : to(to), cap(cap) {}
    };

    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj;
    std::vector<int> cur, h;
    dinic(int n) : n(n), adj(n) {}

    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);

        while (!que.empty()) {
            const int u = que.front();
            que.pop();

            for (int i : adj[u]) {
                auto v = edges[i].to; auto c = edges[i].cap;
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) return true;
                    que.push(v);
                }
            }
        }
        return false;
    }

    T dfs(int u, int t, T f) {
        if (u == t) return f;

        auto r = f;
        for (int &i = cur[u]; i < int(adj[u].size()); ++i) {
            const int j = adj[u][i];
            auto v = edges[j].to; auto c = edges[j].cap;
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));

                edges[j].cap -= a;
                edges[j ^ 1].cap += a;
                r -= a;
                if (r == 0) return f;
            }
        }
        return f - r;
    }

    void addEdge(int u, int v, T c) {
        adj[u].push_back(edges.size());
        edges.emplace_back(v, c);
        adj[v].push_back(edges.size());
        edges.emplace_back(u, 0);
    }

    T maxFlow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
};
