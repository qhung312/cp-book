#pragma once
#include <bits/stdc++.h>
using namespace std;

struct dsu {
    vector<int> f, sz, h;
    int n, mx_siz = 1, num_cc = 0;
    dsu(int nn) : n(nn), num_cc(nn), f(nn), sz(nn, 1), h(nn, 1) {
        iota(f.begin(), f.end(), 0);
    }
    int parent(int u) {
        return u == f[u] ? u : (u = parent(f[u]));
    }
    void join(int u, int v) {
        u = parent(u), v = parent(v);
        if (u == v) return;
        num_cc--;
        if (h[u] < h[v]) {
            f[u] = v; sz[v] += sz[u];
        } else if (h[u] > h[v]) {
            f[v] = u; sz[u] += sz[v];
        } else {
            f[u] = v; sz[v] += sz[u]; h[v]++;
        }
        mx_siz = max(mx_siz, sz[u]);
        mx_siz = max(mx_siz, sz[v]);
    }
    int getCCCount() const { return num_cc; }
    int getMaxSize() const { return mx_siz; }
    int sizeOf(int u) { return sz[parent(u)]; }
    bool same(int u, int v) { return parent(u) == parent(v); }
};
