#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <int _mod1, int _mod2, int _base>
class StringHash {
 private:
  static constexpr int mod1 = _mod1;
  static constexpr int mod2 = _mod2;
  static constexpr int base = _base;

  int n;
  vector<int> h1, h2;
  vector<int> p1, p2;

 public:
  explicit StringHash(const string& s)
      : n(s.length()), h1(n + 1), h2(n + 1), p1(n + 1), p2(n + 1) {
    p1[0] = p2[0] = 1;
    for (int i = 1; i <= n; i++) {
      p1[i] = 1LL * p1[i - 1] * base % mod1;
      p2[i] = 1LL * p2[i - 1] * base % mod2;
    }
    for (int i = 0; i < n; i++) {
      // Calculate every prefix hash value
      // Implementation expects lowercase alphabet characters, might want to
      // change this as needed
      h1[i + 1] = (1LL * h1[i] * base % mod1 + s[i] - 'a' + 1) % mod1;
      h2[i + 1] = (1LL * h2[i] * base % mod2 + s[i] - 'a' + 1) % mod2;
    }
  }

  pair<int, int> substr_hash(int l, int r) {
    int v1 = (h1[r + 1] - 1LL * h1[l] * p1[r - l + 1] % mod1 + mod1) % mod1;
    int v2 = (h2[r + 1] - 1LL * h2[l] * p2[r - l + 1] % mod2 + mod2) % mod2;
    return {v1, v2};
  }
};
