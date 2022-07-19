#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class T>
struct matrix {
    vector<vector<T>> a;
    matrix(int n, int m, const T &v = 0) {
        a.resize(n, vector<T>(m, v));
    }
    matrix(const matrix<T> &o) {
        int n = o.nrows(), m = o.ncols();
        a.resize(n, vector<T>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) a[i][j] = o[i][j];
        }
    }
    int nrows() const { return a.size(); }
    int ncols() const { return a[0].size(); }
    vector<T> &operator[](int i) { return a[i]; }
    const vector<T> &operator[](int i) const { return a[i]; }

    matrix<T> operator+() { return matrix<T>(*this); }
    matrix<T> operator-() {
        matrix<T> ans(*this);
        for (int i = 0; i < ans.nrows(); i++) {
            for (int j = 0; j < ans.ncols(); j++) {
                ans[i][j] = -ans[i][j];
            }
        }
        return ans;
    }

    matrix<T> &operator+=(const matrix<T> &o) {
        for (int i = 0; i < this->nrows(); i++) {
            for (int j = 0; j < this->ncols(); j++) {
                a[i][j] += o[i][j];
            }
        }
        return *this;
    }
    matrix<T> &operator-=(const matrix<T> &o) {
        for (int i = 0; i < this->nrows(); i++) {
            for (int j = 0; j < this->ncols(); j++) {
                a[i][j] -= o[i][j];
            }
        }
        return *this;
    }
    matrix<T> &operator*=(const matrix<T> &o) {
        vector<vector<T>> ans(this->nrows(), vector<T>(o.ncols()));
        for (int i = 0; i < this->nrows(); i++) {
            for (int j = 0; j < o.ncols(); j++) {
                for (int k = 0; k < this->ncols(); k++) {
                    ans[i][j] += a[i][k] * o[k][j];
                }
            }
        }
        a = ans;
        return *this;
    }
    friend matrix<T> operator+(const matrix<T> &lhs, const matrix<T> &rhs) {
        matrix<T> ans(lhs);
        ans += rhs;
        return ans;
    }
    friend matrix<T> operator-(const matrix<T> &lhs, const matrix<T> &rhs) {
        matrix<T> ans(lhs);
        ans -= rhs;
        return ans;
    }
    friend matrix<T> operator*(const matrix<T> &lhs, const matrix<T> &rhs) {
        matrix<T> ans(lhs);
        ans *= rhs;
        return ans;
    }

    friend ostream &operator<<(ostream &out, matrix<T> x) {
        out << "Matrix of size " << x.nrows() << "x" << x.ncols() << ":\n";
        for (int i = 0; i < x.nrows(); i++) {
            for (int j = 0; j < x.ncols(); j++) out << x[i][j] << ' ';
            out << '\n';
        }
        return out;
    }
};
