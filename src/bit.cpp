#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct fenwick {
	int n;
	vector<T> a;
	fenwick(int nn) : n(nn), a(nn + 1) {}

	void add(int i, T v) {
		for (i++; i <= n; i += i & -i) a[i] += v;
	}
	T prefix(int i) {
		T ans = 0;
		for (i++; i >= 1; i -= i & -i) ans += a[i];
		return ans;
	}
	T query(int l, int r) {
		return prefix(r) - prefix(l-1);
	}
};
