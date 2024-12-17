#pragma once
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <functional>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
 
using namespace std;
 
class EulerianPathUndirected {
private:
  int n;
  vector<vector<int>> adj;
 
  // Maintain list of all edges. This is used to quickly find the reversed edge
  // of given edge i (stored at index i ^ 1)
  vector<bool> visited;
  vector<pair<int, int>> edges;
 
  bool is_connected() const {
    // Check if all edges are reachable from a single vertex
    int first;
    for (first = 0; first < n && adj[first].size() == 0; first++)
      ;
    if (first == n) {
      return true;
    }
 
    vector<bool> vis(n, false);
    stack<int> st;
    st.push(first);
    vis[first] = true;
    while (!st.empty()) {
      int u = st.top();
      st.pop();
      for (int i : adj[u]) {
        int v = edges[i].second;
        if (!vis[v]) {
          vis[v] = true;
          st.push(v);
        }
      }
    }
    for (int i = 0; i < n; i++) {
      if (!vis[i] && adj[i].size() > 0) {
        return false;
      }
    }
    return true;
  }
 
public:
  explicit EulerianPathUndirected(int n) : n(n), adj(n) {}
 
  void add_edge(int u, int v) {
    // Add edge from u to v
    adj[u].push_back(edges.size());
    edges.emplace_back(u, v);
    visited.push_back(false);
    // Add edge from v to u
    adj[v].push_back(edges.size());
    edges.emplace_back(v, u);
    visited.push_back(false);
  }
 
  bool has_eulerian_cycle() const {
    // Graph should be connected
    if (!is_connected()) {
      return false;
    }
    for (int i = 0; i < n; i++) {
      if (adj[i].size() % 2 != 0) {
        return false;
      }
    }
    return true;
  }
 
  bool has_eulerian_path() const {
    // Graph should be connected
    if (!is_connected()) {
      return false;
    }
    int odd_degree_count = 0;
    for (int i = 0; i < n; i++) {
      if (adj[i].size() % 2 != 0) {
        odd_degree_count++;
      }
    }
    return odd_degree_count == 0 || odd_degree_count == 2;
  }
 
  bool euler_path_contains(int u) const {
    if (!has_eulerian_path()) {
      return false;
    }
    int first;
    for (first = 0; first < n && adj[first].size() == 0; first++)
      ;
    if (first == n) {
      return true;
    }
    vector<bool> vis(n, false);
    stack<int> st;
    st.push(first);
    vis[first] = true;
    while (!st.empty()) {
      int u = st.top();
      st.pop();
      for (int i : adj[u]) {
        int v = edges[i].second;
        if (!vis[v]) {
          vis[v] = true;
          st.push(v);
        }
      }
    }
    return vis[u];
  }
 
  vector<int> find_eulerian_path(int start_if_cycle = 0) {
    assert(has_eulerian_path() || has_eulerian_cycle());
 
    // If we have a path but not a cycle, we need to add dummy edge from
    // start to end
    int start = -1, end = -1;
    if (has_eulerian_path() && !has_eulerian_cycle()) {
      for (int i = 0; i < n; i++) {
        if (adj[i].size() % 2 != 0) {
          if (start == -1) {
            start = i;
          } else {
            end = i;
          }
        }
      }
      add_edge(start, end);
    }
 
    // Perform Hierholzer's algorithm
    // See: https://cp-algorithms.com/graph/euler_path.html
    vector<int> path;
    stack<int> st;
 
    // If we have a path, we must start from `start`
    // Otherwise, we can start from any vertex, so we let the user decide
    if (start == -1) {
      st.emplace(start_if_cycle);
    } else {
      st.emplace(start);
    }
    while (!st.empty()) {
      int u = st.top();
      // Find the first unvisited edge from u
      // Pop shared data structure to improve performance
      while (!adj[u].empty() && visited[adj[u].back()]) {
        adj[u].pop_back();
      }
      if (adj[u].empty()) {
        path.push_back(u);
        st.pop();
      } else {
        int i = adj[u].back();
        visited[i] = visited[i ^ 1] = true;
        adj[u].pop_back();
        st.push(edges[i].second);
      }
    }
 
    // Remove dummy edge from the result
    if (start != -1) {
      assert(path.back() == start);
      assert(path.size() >= 3);
      path.pop_back();
      if (path[1] == end) {
        reverse(path.begin() + 1, path.end());
      }
    }
 
    return path;
  }
};
