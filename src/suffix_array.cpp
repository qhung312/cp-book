class SuffixArray {
 private:
  int n;
  string s;

  vector<int> ord, cls;

  int ceil_log(int n) {
    int k = 0;
    while ((1 << k) < n) {
      k++;
    }
    return k;
  }

  void build_sa() {
    // Do the first sort to build initial ord and cls
    // We can sort this in O(nlogn), since the subsequent parts are also
    // O(nlogn)
    ord.resize(n);
    cls.resize(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) { return s[a] < s[b]; });
    cls[ord[0]] = 0;
    for (int i = 1; i < n; i++) {
      cls[ord[i]] = cls[ord[i - 1]];
      if (s[ord[i]] != s[ord[i - 1]]) {
        cls[ord[i]]++;
      }
    }
    // Build with step k from 1 to ceil(log2(n))
    vector<int> new_ord(n), cnt(n), new_cls(n);
    int maxk = ceil_log(n);
    for (int k = 1; k <= maxk; k++) {
      // Sort everything by the second half of the previous iteration
      for (int i = 0; i < n; i++) {
        new_ord[i] = ord[i] - (1 << (k - 1));
        if (new_ord[i] < 0) new_ord[i] += n;
      }
      // Then sort again using the first half
      fill(cnt.begin(), cnt.end(), 0);
      for (int i = 0; i < n; i++) {
        cnt[cls[i]]++;
      }
      for (int i = 1; i < n; i++) {
        cnt[i] += cnt[i - 1];
      }
      for (int i = n - 1; i >= 0; i--) {
        ord[--cnt[cls[new_ord[i]]]] = new_ord[i];
      }
      new_cls[ord[0]] = 0;
      for (int i = 1; i < n; i++) {
        pair<int, int> prev = {cls[ord[i - 1]],
                               cls[(ord[i - 1] + (1 << (k - 1))) % n]};
        pair<int, int> cur = {cls[ord[i]], cls[(ord[i] + (1 << (k - 1))) % n]};
        new_cls[ord[i]] = new_cls[ord[i - 1]];
        if (prev != cur) {
          new_cls[ord[i]]++;
        }
      }
      cls.swap(new_cls);
    }
  }

 public:
  explicit SuffixArray(const string& _s) : s(_s), n(_s.length()) {}

  vector<int> build_suffix_array(bool cyclic = false) {
    if (!cyclic) {
      // Add a character smaller than any other character in the string, so we
      // can't compare cyclically
      // Might want to change this character in some cases
      s += '$';
      n++;
    }
    build_sa();
    if (!cyclic) {
      s.pop_back();
      n--;
      ord.erase(ord.begin());
      cls.pop_back();
    }
    return ord;
  }

  vector<int> get_lcp_array() const {
    // Build LCP array based on Kasai's algorithm
    // Reference: https://cp-algorithms.com/string/suffix-array.html
    vector<int> rank(n), lcp(n - 1);
    for (int i = 0; i < n; i++) {
      rank[ord[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
      if (rank[i] == n - 1) {
        k = 0;
        continue;
      }
      int j = ord[rank[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
        k++;
      }
      lcp[rank[i]] = k;
      if (k) k--;
    }
    return lcp;
  }
};
