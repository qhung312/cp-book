#include <bits/stdc++.h>
using namespace std;

/*
Wavelet tree implementation that provides the following functions:
- count_equal(x, i, j): number of elements in range [i, j] with value x
- count_leq(x, i, j): number of elements in range [i, j] with value <= x
- count_in_range(x, y, i, j): number of elements in range [i, j] with value in
range [x, y]
- k_sorted(k, i, j): value of k-th element (0-indexed) after sorting range [i,
j]

All operations are O(logn)
*/

template <typename T> struct wavelet_tree {
    T l, r;
    wavelet_tree<T> *lt;
    wavelet_tree<T> *rt;
    vector<T> a;
    vector<int> mleft, mright;
    wavelet_tree(const vector<T> &_a, T _l, T _r)
        : a(_a), l(_l), r(_r), lt(nullptr), rt(nullptr) {
        T s = (l + r) / 2;
        int n = a.size();
        mleft.resize(n);
        mright.resize(n);
        int cntl = 0, cntr = 0;
        vector<T> lv, rv;
        for (int i = 0; i < n; i++) {
            if (a[i] <= s) {
                cntl++;
                lv.push_back(a[i]);
            } else {
                cntr++;
                rv.push_back(a[i]);
            }
            mleft[i] = cntl - 1;
            mright[i] = cntr - 1;
        }
        if (l != r) {
            // need to split further
            if (!lv.empty())
                lt = new wavelet_tree<T>(lv, l, s);
            if (!rv.empty())
                rt = new wavelet_tree<T>(rv, s + 1, r);
        }
    }

    void clear() {
        if (lt) {
            lt->clear();
            delete lt;
            lt = nullptr;
        }
        if (rt) {
            rt->clear();
            delete rt;
            rt = nullptr;
        }
    }
    ~wavelet_tree() { clear(); }

    int count_equal(T x, int i) {
        if (i == -1)
            return 0;
        if (l == r)
            return i + 1;
        T s = (l + r) / 2;
        if (x <= s) {
            return lt ? lt->count_equal(x, mleft[i]) : 0;
        } else {
            return rt ? rt->count_equal(x, mright[i]) : 0;
        }
    }

    int count_equal(T x, int i, int j) {
        int ans = count_equal(x, j);
        if (i > 0)
            ans -= count_equal(x, i - 1);
        return ans;
    }

    int count_leq(T x, int i) {
        if (i == -1)
            return 0;
        if (x < l)
            return 0;
        if (x >= r)
            return i + 1;
        T s = (l + r) / 2;
        int ans = 0;
        if (lt)
            ans += lt->count_leq(x, mleft[i]);
        if (rt)
            ans += rt->count_leq(x, mright[i]);
        return ans;
    }

    int count_leq(T x, int i, int j) {
        int ans = count_leq(x, j);
        if (i > 0)
            ans -= count_leq(x, i - 1);
        return ans;
    }
    int count_in_range(T x, T y, int i, int j) {
        return count_leq(y, i, j) - count_leq(x - 1, i, j);
    }

    T k_sorted(int k, int i, int j) {
        if (l == r) {
            if (i == -1)
                i = 0;
            return l;
        }
        if (i == -1)
            i = 0;
        T s = (l + r) / 2;
        int c = mleft[j] - (i > 0 ? mleft[i - 1] : -1);
        if (k < c) {
            int il = i > 0 ? mleft[i - 1] + 1 : 0;
            return lt->k_sorted(k, il, mleft[j]);
        } else {
            int ir = i > 0 ? mright[i - 1] + 1 : 0;
            return rt->k_sorted(k - c, ir, mright[j]);
        }
    }
};
