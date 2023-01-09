#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct matrix {
    vector<vector<T>> a;
    int n, m;
    matrix(int _n, int _m) : n(_n), m(_m) { a.resize(_n, vector<T>(_m)); }

    vector<T> &operator[](int i) { return a[i]; }
    const vector<T> &operator[](int i) const { return a[i]; }

    matrix<T> &operator*=(const matrix<T>& o) {
        vector<vector<T>> ans(n, vector<T>(o.m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < o.m; j++) {
                for (int k = 0; k < m; k++) {
                    ans[i][j] += a[i][k] * o[k][j];
                }
            }
        }
    }
    friend matrix<T> operator*(const matrix<T>& lhs, const matrix<T>& rhs) {
        matrix<T> ans(lhs); ans *= rhs; return ans;
    }
};

