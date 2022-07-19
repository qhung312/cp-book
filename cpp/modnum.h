#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int mod = 1000000007;
int norm_modnum(int x) {
    if (x < 0) {
        x += mod;
    }
    if (x >= mod) {
        x -= mod;
    }
    return x;
}
template<class T>
T power(T a, ll b) {
    T ans = 1;
    while (b) {
        if (b & 1) {
            ans *= a;
        }
        a *= a;
        b >>= 1;
    }
    return ans;
}
struct modnum {
    int x;
    modnum(int nx = 0) { if (nx >= 0 && nx < mod) x = nx; else x = norm_modnum(nx % mod); }
    modnum(ll nx) : x(norm_modnum(nx % mod)) {}
    int val() const {
        return x;
    }
    modnum operator+() const { return modnum(x); }
    modnum operator-() const { return modnum(norm_modnum(mod - x)); }
    modnum &operator+=(const modnum &o) { x = norm_modnum(x + o.x); return *this; }
    modnum &operator-=(const modnum &o) { x = norm_modnum(x - o.x); return *this; }
    modnum &operator*=(const modnum &o) { x = (ll) x * o.x % mod; return *this; }
    modnum &operator/=(const modnum &o) { return *this *= o.inv(); }

    modnum inv() const {
        return power(*this, mod - 2);
    }

    friend modnum operator+(const modnum &a, const modnum &b) { modnum ans = a; ans += b; return ans; }
    friend modnum operator-(const modnum &a, const modnum &b) { modnum ans = a; ans -= b; return ans; }
    friend modnum operator*(const modnum &a, const modnum &b) { modnum ans = a; ans *= b; return ans; }
    friend modnum operator/(const modnum &a, const modnum &b) { modnum ans = a; ans /= b; return ans; }
    friend istream &operator>>(istream &in, modnum &a) { ll v; in >> v; a = modnum(v); return in; }

    modnum &operator++() { return *this += modnum(1); }
    modnum &operator--() { return *this -= modnum(1); }
    modnum &operator++(int) { return ++(*this); }
    modnum &operator--(int) { return --(*this); }
};
