#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int mod = 1000000007;
int norm(int x) {
	if (x < 0) x += mod;
	if (x >= mod) x -= mod;
	return x;
}
struct modnum {
	int x;
	modnum(ll _x = 0) : x(norm(_x % mod)) {}

	modnum operator+(modnum o) { return modnum(norm(x + o.x)); }
	modnum operator-(modnum o) { return modnum(norm(x - o.x)); }
	modnum operator*(modnum o) { return modnum((ll) x * o.x % mod); }
	modnum operator/(modnum o) { return *this * o.inv(); }
	modnum inv() const { return pow(mod - 2); }

	modnum pow(ll b) const {
		modnum ans(1);
		modnum a = *this;
		for (; b; a = a * a, b /= 2) {
			if (b % 2 == 1) {
				ans = ans * a;
			}
		}
		return ans;
	}
};
