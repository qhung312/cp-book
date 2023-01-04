#include <bits/stdc++.h>
using namespace std;

struct suffix_array {
	int n;
	string s;
	vector<int> lcp;
	const int ALPHA = 256;
	suffix_array(const string& _s) : s(_s), n(_s.length()) {}

	vector<int> solve_cyclic() {
		int logn = (__builtin_popcount(n) == 1 ? 31 : 32) - __builtin_clz(n);

		vector<int> p(n), c(n), cnt(ALPHA);
		for (int i = 0; i < n; i++) cnt[s[i]]++;
		for (int i = 1; i < ALPHA; i++) cnt[i] += cnt[i-1];
		for (int i = n - 1; i >= 0; i--) p[--cnt[s[i]]] = i;

		int classes = 0;
		for (int i = 1; i < n; i++) {
			if (s[p[i]] != s[p[i - 1]]) classes++;
			c[p[i]] = classes;
		}

		vector<int> np(n), nc(n);
		cnt.resize(n);
		for (int k = 1; k <= logn; k++) {
			for (int i = 0; i < n; i++) {
				np[i] = p[i] - (1 << (k-1));
				if (np[i] < 0) np[i] += n;
			}
			fill(cnt.begin(), cnt.end(), 0);

			for (int i : np) cnt[c[i]]++;
			for (int i = 1; i < n; i++) cnt[i] += cnt[i-1];
			for (int i = n-1; i >= 0; i--) p[--cnt[c[np[i]]]] = np[i];

			classes = 0;
			nc[p[0]] = 0;
			for (int i = 1; i < n; i++) {
				pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << (k - 1))) % n]};
				pair<int, int> last = {c[p[i - 1]], c[(p[i - 1] + (1 << (k - 1))) % n]};
				if (cur > last) classes++;
				nc[p[i]] = classes;
			}
			swap(c, nc);
		}

		build_lcp(p);
		return p;
	}

	void build_lcp(const vector<int>& p) {
		vector<int> pos(n);
		lcp.resize(n - 1);
		for (int i = 0; i < n; i++) pos[p[i]] = i;

		int k = 0;
		for (int i = 0; i < n; i++) {
			if (pos[i] == n - 1) {
				k = 0;
				continue;
			}
			int j = p[pos[i] + 1];
			while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
			lcp[pos[i]] = k;
			if (k) k--;
		}
	}

	vector<int> solve_non_cyclic(char e = '$') {
		n++; s += e;
		auto a = solve_cyclic();
		n--; s.pop_back();
		a.erase(a.begin());
		lcp.erase(lcp.begin());
		return a;
	}
};
