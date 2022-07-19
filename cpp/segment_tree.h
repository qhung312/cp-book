#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct segment_tree {
    int n;
    vector<T> st;
    segment_tree(int n) : n(n), st(4 * n + 100) {}
    segment_tree(const vector<T> &init) : segment_tree(init.size()) {
        function<void(int, int, int)> build = [&](int p, int l, int r) -> void {
            if (l == r) {
                st[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            merge(p);
        };
        build(1, 0, n - 1);
    }
    void merge(int p) {
        st[p] = st[2 * p] + st[2 * p + 1];
    }
    void modify(int p, int l, int r, int i, const T &x) {
        if (l > i || r < i) {
            return;
        }
        if (l == r) {
            st[p] = x;
            return;
        }
        int m = (l + r) / 2;
        modify(2 * p, l, m, i, x);
        modify(2 * p + 1, m + 1, r, i, x);
        merge(p);
    }
    void modify(int i, const T &x) {
        modify(1, 0, n - 1, i, x);
    }
    T query(int p, int l, int r, int i, int j) {
        if (l >= i && r <= j) return st[p];
        if (r < i || l > j) return T();
        int m = (l + r) / 2;
        T ln = query(2 * p, l, m, i, j);
        T rn = query(2 * p + 1, m + 1, r, i, j);
        return ln + rn;
    }
    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

struct Info {
    Info() {} // Constructor for bad values
    Info() {} // Constructor for good values
    friend Info operator +(const Info &a, const Info &b) {}
};
