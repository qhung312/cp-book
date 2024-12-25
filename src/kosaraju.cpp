#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <stack>
#include <vector>

using namespace std;

class SCCGraph {
private:
  int n;
  vector<vector<int>> graph, reversed_graph;

  // Store some useful information about the contracted SCCs
  vector<vector<int>> scc;
  vector<vector<int>> condensation_graph;
  vector<int> topo;
  vector<int> comp;

public:
  explicit SCCGraph(int _n) : n(_n), graph(n), reversed_graph(n), comp(n) {}

  vector<vector<int>> get_scc() const { return scc; }

  vector<vector<int>> get_condensation_graph() const {
    return condensation_graph;
  }

  vector<int> get_component_mapping() const { return comp; }

  vector<int> get_topological_order() const { return topo; }

  void add_edge(int from, int to) {
    graph[from].push_back(to);
    reversed_graph[to].push_back(from);
  }

  void solve() {
    vector<bool> visited(n);
    stack<int> stk;
    function<void(int)> dfs = [&](int u) -> void {
      visited[u] = true;
      for (int v : graph[u]) {
        if (!visited[v]) {
          dfs(v);
        }
      }
      stk.push(u);
    };
    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        dfs(i);
      }
    }
    // Reverse the edges, and do a DFS to contract the SCCs
    fill(visited.begin(), visited.end(), false);
    dfs = [&](int u) -> void {
      scc.back().push_back(u);
      comp[u] = scc.size() - 1;
      visited[u] = true;
      for (int v : reversed_graph[u]) {
        if (!visited[v]) {
          dfs(v);
        }
      }
    };
    while (!stk.empty()) {
      int u = stk.top();
      stk.pop();
      if (!visited[u]) {
        scc.push_back({});
        condensation_graph.push_back({});
        topo.push_back(scc.size() - 1);
        dfs(u);
      }
    }
    // Go over the original edges to build condensation graph
    for (int i = 0; i < n; i++) {
      for (int j : graph[i]) {
        if (comp[i] != comp[j]) {
          condensation_graph[comp[i]].push_back(comp[j]);
        }
      }
    }
  }
};
