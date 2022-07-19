#pragma once
#include <bits/stdc++.h>
using namespace std;

struct twosat {
    int n;
    vector<vector<int>> adj;
    vector<bool> ans;
    twosat(int n) : n(n), adj(2 * n), ans(2 * n) {}
    int negate(int x) const {
        if (x >= 0 && x < n) {
            x += n;
        } else {
            x -= n;
        }
        return x;
    }
    void addClause(int x, int y) {
        adj[negate(x)].push_back(y);
        adj[negate(y)].push_back(x);
    }
    bool solve() {
        vector<vector<int>> scc;
        vector<int> low(2 * n);
        vector<int> num(2 * n, -1);
        vector<bool> vis(2 * n);
        stack<int> s;
        int clk = 0;
        function<void(int)> dfs1 = [&](int u) -> void {
            low[u] = num[u] = clk++;
            vis[u] = true;
            s.push(u);
            for (int v : adj[u]) {
                if (num[v] == -1) dfs1(v);
                if (vis[v]) low[u] = min(low[u], low[v]);
            }
            if (low[u] == num[u]) {
                vector<int> vv;
                while (true) {
                    int v = s.top(); s.pop(); vis[v] = false;
                    vv.push_back(v);
                    if (v == u) break;
                }
                scc.push_back(vv);
            }
        };
        for (int i = 0; i < 2 * n; i++) {
            if (num[i] == -1) dfs1(i);
        }
        vector<int> c(2 * n);
        for (int i = 0; i < scc.size(); i++) {
            for (int u : scc[i]) {
                c[u] = i;
            }
        }
        for (int i = 0; i < n; i++) {
            if (c[i] == c[negate(i)]) return false;
        }
        int sn = scc.size();
        vector<vector<int>> adj2(sn);
        vector<bool> vis2(sn);
        vector<int> t;
        for (int i = 0; i < 2 * n; i++) {
            for (int v : adj[i]) {
                if (c[i] != c[v]) {
                    adj2[c[i]].push_back(c[v]);
                }
            }
        }
        function<void(int)> dfs2 = [&](int u) -> void {
            vis2[u] = true;
            for (int v : adj2[u]) {
                if (!vis2[v]) {
                    dfs2(v);
                }
            }
            t.push_back(u);
        };
        for (int i = 0; i < sn; i++) if (!vis2[i]) dfs2(i);
        reverse(t.begin(), t.end());
        vector<int> p(sn);
        for (int i = 0; i < sn; i++) {
            p[t[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            if (p[c[i]] > p[c[negate(i)]]) {
                ans[i] = true;
            } else {
                ans[negate(i)] = true;
            }
        }
        return true;
    }
    bool operator[](int i) const { return ans[i]; }
};
