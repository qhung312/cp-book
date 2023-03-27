#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll inf = 1E14;
struct line {
    ll a, b;
    line() : a(0), b(inf) {}
    line(ll _a, ll _b) : a(_a), b(_b) {}
    ll operator()(ll x) const { return a * x + b; }
};

struct lichao_tree {
    int n;
    vector<line> tree;
    lichao_tree(int _n) : n(_n), tree(4 * _n + 5) {}

    void add_line(const line &l) { add_line(1, 0, n - 1, l); }
    ll query(ll x) { return query(1, 0, n - 1, x); }

    void add_line(int p, int l, int r, const line &ln) {
        if (l == r) {
            if (ln(l) < tree[p](l))
                tree[p] = ln;
            return;
        }

        int m = (l + r) / 2;
        bool left = ln(l) < tree[p](l);
        bool mid = ln(m + 1) < tree[p](m + 1);
        if (mid)
            tree[p] = ln;
        if (left != mid) {
            add_line(2 * p, l, m, ln);
        } else {
            add_line(2 * p + 1, m + 1, r, ln);
        }
    }
    ll query(int p, int l, int r, ll x) {
        if (l == r)
            return tree[p](x);
        int m = (l + r) / 2;
        if (x <= m) {
            return min(tree[p](x), query(2 * p, l, m, x));
        } else {
            return min(tree[p](x), query(2 * p + 1, m + 1, r, x));
        }
    }
};
