#pragma once
#include <bits/stdc++.h>
using namespace std;

struct dijkstra_graph {
    using edge = pair<long long, int>;
    vector<vector<pair<int, long long>>> adj;
    priority_queue<edge, vector<edge>, greater<edge>> q;
    vector<long long> dist;
    vector<int> prv;
    int s = -1;
    dijkstra_graph(int n) : adj(n), dist(n, LONG_LONG_MAX), prv(n) {}
    void addEdge(int a, int b, long long w) {
        adj[a].emplace_back(b, w);
    }
    void solve(int ns) {
        if (ns == s) {
            return;
        }
        s = ns;
        fill(dist.begin(), dist.end(), LONG_LONG_MAX);
        prv[s] = s;
        dist[s] = 0;
        q.emplace(0, s);
        while (!q.empty()) {
            auto e = q.top();
            long long d = e.first;
            int u = e.second;
            q.pop();

            if (d > dist[u]) {
                continue;
            }
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    prv[v] = u;
                    dist[v] = dist[u] + w;
                    q.emplace(dist[v], v);
                }
            }
        }
    }
    int getPrv(int u) const { return prv[u]; }
    long long operator[](int i) const { return dist[i]; }
};
