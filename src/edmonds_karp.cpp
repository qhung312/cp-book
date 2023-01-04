#include <bits/stdc++.h>
using namespace std;

template<typename flow_t = int>
struct edmonds_karp {
	struct Edge {
		int to;
		flow_t cap;
		Edge(int to, flow_t cap) : to(to), cap(cap) {}
	};

	vector<Edge> edges;
	vector<vector<int>> adj;
	vector<int> prevNode, prevEdge;

	int s = -1, t = -1;
	flow_t mf = 0;

	edmonds_karp(int n) : adj(n), prevNode(n, -1), prevEdge(n, -1) {}

	void addEdge(int u, int v, flow_t c) {
		int siz = edges.size();
		edges.emplace_back(v, c);
		edges.emplace_back(u, 0);
		adj[u].push_back(siz);
		adj[v].push_back(siz + 1);
	}

	bool bfs() {
		fill(prevNode.begin(), prevNode.end(), -1);
		fill(prevEdge.begin(), prevEdge.end(), -1);
		queue<int> q;
		q.push(s);
		prevNode[s] = s;

		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int e : adj[u]) {
				int to = edges[e].to;
				flow_t cap = edges[e].cap;
				if (cap > 0 && prevNode[to] == -1) {
					prevNode[to] = u;
					prevEdge[to] = e;
					q.push(to);
				}
			}
		}
		return prevNode[t] != -1;
	}

	flow_t maxFlow(int ss, int tt) {
		if (ss == s && tt == t) return mf;

		mf = 0; s = ss; t = tt;
		while (bfs()) {
			vector<flow_t> w;
			vector<int> e;
			int cur = t;
			while (cur != s) {
				w.push_back(edges[prevEdge[cur]].cap);
				e.push_back(prevEdge[cur]);
				cur = prevNode[cur];
			}

			flow_t flow = *min_element(w.begin(), w.end());
			mf += flow;
			for (int x : e) {
				edges[x].cap -= flow;
				edges[x ^ 1].cap += flow;
			}
		}
		return mf;
	}
};
