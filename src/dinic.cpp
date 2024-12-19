#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

template <typename T> class Dinic {
private:
  vector<int> ptr;

  bool bfs(int source, int sink) {
    // Returns true if source can reach sink using only positive capacity edges.
    fill(level.begin(), level.end(), -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i : adj[u]) {
        int v = edges[i].to;
        int remainingCapacity = edges[i].capacity;
        if (remainingCapacity > 0 && level[v] == -1) {
          level[v] = level[u] + 1;
          q.push(v);
        }
      }
    }
    return level[sink] != -1;
  }

  T dfs(int u, int sink, T flow_pushed) {
    if (u == sink)
      return flow_pushed;
    if (flow_pushed == 0)
      return 0;

    T flow = 0;
    for (int &i = ptr[u]; i < adj[u].size(); i++) {
      int v = edges[adj[u][i]].to;
      int edgeCapacity = edges[adj[u][i]].capacity;

      if (edgeCapacity == 0 || level[v] != level[u] + 1)
        continue;

      T pushed = dfs(v, sink, min(flow_pushed, edgeCapacity));
      flow += pushed;
      edges[adj[u][i]].capacity -= pushed;
      edges[adj[u][i] ^ 1].capacity += pushed;
      if (flow == flow_pushed)
        return flow_pushed;
    }
    return flow;
  }

public:
  struct Edge {
    int from, to;
    T capacity;
    explicit Edge(int _from, int _to, T _capacity)
        : from(_from), to(_to), capacity(_capacity) {}
  };

  // Expose internal data structures to make it easier to work with graph
  // after running max flow. This is helpful for many problems (e.g min cut).
  vector<vector<int>> adj;
  vector<Edge> edges;
  vector<int> level;

  explicit Dinic(int _n) : adj(_n), level(_n), ptr(_n) {}

  void add_edge(int from, int to, T capacity) {
    adj[from].push_back(edges.size());
    edges.emplace_back(from, to, capacity);
    adj[to].push_back(edges.size());
    edges.emplace_back(to, from, 0);
  }

  T max_flow(int source, int sink) {
    T flow = 0;
    while (bfs(source, sink)) {
      fill(ptr.begin(), ptr.end(), 0);
      flow += dfs(source, sink, std::numeric_limits<T>::max());
    }
    return flow;
  }
};
