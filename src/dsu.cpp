#include <bits/stdc++.h>
using namespace std;

struct dsu {
	vector<int> par;
	dsu(int n) : par(n, -1) {}

	int parent(int u) {
		return par[u] < 0 ? u : (par[u] = parent(par[u]));
	}
	bool merge(int u, int v) {
		u = parent(u); v = parent(v);
		if (u == v) return false;
		if (par[u] < par[v]) swap(u, v);
		par[v] += par[u];
		par[u] = v;
		return true;
	}
	bool same(int u, int v) {
		return parent(u) == parent(v);
	}
	int size_of(int u) {
		return -par[parent(u)];
	}
};

