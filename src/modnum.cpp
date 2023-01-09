#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1000000007;

struct modnum {
    int x;
    modnum(int64_t _x = 0) : x(int(_x % MOD)) { if (x < 0) x += MOD; }
    int value() const { return x; }
    modnum inv() const { return pow(MOD-2); }

    modnum& operator+=(const modnum& o) {
        x += o.x;
        if (x >= MOD) x -= MOD;
        return *this;
    }
    modnum& operator-=(const modnum& o) {
        x -= o.x;
        if (x < 0) x += MOD;
        return *this;
    }
    modnum& operator*=(const modnum& o) {
        x = int(int64_t(x) * int64_t(o.x) % MOD);
        return *this;
    }
    modnum& operator/=(const modnum& o) {
        return *this *= o.inv();
    }

    friend modnum operator+(const modnum& a, const modnum& b) {
        modnum ans = a;
        ans += b;
        return ans;
    }
    friend modnum operator-(const modnum& a, const modnum& b) {
        modnum ans = a;
        ans -= b;
        return ans;
    }
    friend modnum operator*(const modnum& a, const modnum& b) {
        modnum ans = a;
        ans *= b;
        return ans;
    }
    friend modnum operator/(const modnum& a, const modnum& b) {
        modnum ans = a;
        ans /= b;
        return ans;
    }

    modnum pow(int64_t b) const {
        modnum ans(1);
        modnum a = *this;
        while (b) {
            if (b % 2 == 1) ans = ans * a;
            a *= a; b /= 2;
        }
        return ans;
    }
};

