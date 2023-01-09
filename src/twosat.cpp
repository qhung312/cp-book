#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct twosat {
    int n;
    vector<vector<int>> adj;
    vector<bool> ans;
    twosat(int _n) : n(_n), adj(2*n), ans(2*n), low(2*n, -1), num(2*n, -1), vis(2*n), comp(2*n) {}

    void either(int i, bool x, int j, bool y) {
        int a = (2 * i) ^ x ^ 1, b = (2 * j) ^ y ^ 1;
        adj[a ^ 1].push_back(b);
        adj[b ^ 1].push_back(a);
    }

    bool solve() {
        for (int i = 0; i < 2*n; i++) {
            if (num[i] == -1) {
                dfs(i);
            }
        }
        for (int i = 0; i < 2*n; i++) {
            if (comp[i] == comp[i ^ 1]) {
                return false;
            }
        }

        reverse(topo.begin(), topo.end());
        vector<int> pos(2*n);
        for (int i = 0; i < (int) topo.size(); i++) {
            pos[topo[i]] = i;
        }
        for (int i = 0; i < 2*n; i++) {
            ans[i] = pos[comp[i]] > pos[comp[i^1]];
        }
        return true;
    }

    int clk = 0;
    vector<int> low, num, comp, topo;
    stack<int> stk;
    vector<bool> vis;

    void dfs(int u) {
        low[u] = num[u] = clk++;
        vis[u] = true;
        stk.push(u);
        for (int v : adj[u]) {
            if (num[v] == -1) dfs(v);
            if (vis[v]) low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            topo.push_back(u);
            while (true) {
                int v = stk.top(); stk.pop(); vis[v] = false;
                comp[v] = u;
                if (v == u) break;
            }
        }
    }
    bool operator[](int i) const { return ans[2*i]; }
};

