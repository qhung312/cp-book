#include <iostream>
#include <vector>

using namespace std;

// Expects a tree node, and an update node. Whether the nodes have pending
// updates to be propagated is managed by the base class
template <typename T, typename U>
class BaseLazySegmentTree {
 private:
  int n;
  vector<bool> pending;
  vector<T> tree;

  void update(int p, int l, int r, int i, int j, const U& upd) {
    if (r < i || l > j) return;
    if (i <= l && r <= j) {
      pending[p] = true;
      in_range_update(tree[p], i, j, upd);
      return;
    }
    if (pending[p]) {
      push(tree[p], tree[2 * p], tree[2 * p + 1]);
      pending[p] = false;
      pending[2 * p] = pending[2 * p + 1] = true;
    }
    int m = (l + r) / 2;
    update(2 * p, l, m, i, j, upd);
    update(2 * p + 1, m + 1, r, i, j, upd);
    merge_node(tree[p], tree[2 * p], tree[2 * p + 1]);
  }

  T query(int p, int l, int r, int i, int j) {
    if (r < i || l > j) return T();
    if (i <= l && r <= j) return tree[p];
    if (pending[p]) {
      push(tree[p], tree[2 * p], tree[2 * p + 1]);
      pending[p] = false;
      pending[2 * p] = pending[2 * p + 1] = true;
    }
    int m = (l + r) / 2;
    T left = query(2 * p, l, m, i, j);
    T right = query(2 * p + 1, m + 1, r, i, j);
    T res;
    merge_node(res, left, right);
    return res;
  }

  void build(int p, int l, int r) {
    init(p, l, r, tree[p]);
    if (l == r) return;
    int m = (l + r) / 2;
    build(2 * p, l, m);
    build(2 * p + 1, m + 1, r);
  }

  // Allow users to initialize the tree nodes (e.g set it to some array values)
  virtual void init(int p, int l, int r, T& node) {}

  // Called when a node receives an update for range [i, j], with value upd
  virtual void in_range_update(T& node, int i, int j, const U& upd) = 0;

  // Propagate pending updates from the node to its children
  virtual void push(T& node, T& left, T& right) = 0;

  // Combine results from two child nodes into the parent node
  virtual void merge_node(T& node, const T& left, const T& right) = 0;

 public:
  explicit BaseLazySegmentTree(int _n)
      : n(_n), pending(4 * n + 5), tree(4 * n + 5) {}

  void build() {
    // This must be called separately, since derived `init` can't be found in
    // base constructor
    build(1, 0, n - 1);
  }

  void update(int i, int j, const U& upd) { update(1, 0, n - 1, i, j, upd); }

  T query(int i, int j) { return query(1, 0, n - 1, i, j); }
};
