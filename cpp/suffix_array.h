#pragma once
#include <bits/stdc++.h>
using namespace std;

struct suffix_array {
    int n;
    string s;
    vector<vector<int>> C;
    suffix_array(const string &ss) : s(ss), n(ss.length()) {}

    vector<int> solve_cyclic() {
        C.clear();
        int mk = ceil(log2(n));
        vector<int> p(n), last_p(n);
        vector<int> c(n), last_c(n);
        iota(p.begin(), p.end(), 0);
        sort(p.begin(), p.end(), [&](int i, int j) -> bool {
            return s[i] < s[j];
        });
        int num_classes = 0;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i-1]]) {
                num_classes++;
            }
            c[p[i]] = num_classes;
        }

        last_p = p;
        last_c = c;
        C.push_back(c);

        // solve from k=1 to k=mk
        for (int k = 1; k <= mk; k++) {
            iota(p.begin(), p.end(), 0);
            fill(c.begin(), c.end(), 0);
            vector<vector<int>> cs(n);
            for (int i = 0; i < n; i++) {
                int second_half = (p[i] + (1<<(k-1))) % n;
                cs[last_c[second_half]].push_back(p[i]);
            }
            p.clear();
            for (int i = 0; i < n; i++) {
                for (int j : cs[i]) p.push_back(j);
                cs[i].clear();
            }
            for (int i = 0; i < n; i++) {
                int first_half = p[i];
                cs[last_c[first_half]].push_back(p[i]);
            }
            p.clear();
            for (int i = 0; i < n; i++) {
                for (int j : cs[i]) p.push_back(j);
                cs[i].clear();
            }

            int num_classes = 0;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {last_c[p[i]], last_c[(p[i] + (1<<(k-1))) % n]};
                pair<int, int> last = {last_c[p[i-1]], last_c[(p[i-1] + (1<<(k-1))) % n]};
                if (cur > last) {
                    num_classes++;
                }
                c[p[i]] = num_classes;
            }
            last_p = p;
            last_c = c;
            C.push_back(c);
        }
        return p;
    }

    vector<int> solve_non_cyclic(char e = '$') {
        n++; s += e;
        auto a = solve_cyclic();
        n--; s.pop_back();
        // filter suffix with extra character
        vector<int> b;
        for (int x : a) if (x != n) b.push_back(x);
        return b;
    }
};
