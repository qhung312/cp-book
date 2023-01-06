#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct seg_tree {
	int n;
	vector<T> tree;
	seg_tree(int _n) : n(_n), tree(4 * _n + 5) {}

	void modify(int i, const T& x) { modify(1, 0, n-1, i, x); }
	T query(int l, int r) { return query(1, 0, n-1, l, r); }

	void modify(int p, int l, int r, int i, const T& x) {
		if (l > i || r < i) return;
		if (l == r) { tree[p] = x; return; }

		int m = (l + r) / 2;
		modify(2*p, l, m, i, x);
		modify(2*p+1, m+1, r, i, x);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	T query(int p, int l, int r, int i, int j) {
		if (l >= i && r <= j) return tree[p];
		if (r < i || l > j) return T();

		int m = (l + r) / 2;
		T left = query(2*p, l, m, i, j);
		T right = query(2*p+1, m+1, r, i, j);
		return left + right;
	}
};

struct info {
	info() {}
	info() {}
	friend info operator+(const info& a, const info& b) {
	}
};

