#include <bits/stdc++.h>

using namespace std;

const int64_t INF = 1e18;

struct Edge {
    int v, w;
    Edge(int v_, int w_) : v(v_), w(w_) {}
};

struct Graph {
    int n;
    vector<vector<Edge>> adj;
    vector<int64_t> dist;
    vector<bool> mark;

    Graph(int n_) : n(n_), adj(n_), dist(n_), mark(n_) {}

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
    }

    void runBellmanFord(int s) {
        fill(dist.begin(), dist.end(), INF);
        fill(mark.begin(), mark.end(), false);
        dist[s] = 0;

        for (int i = 0; i < n - 1; i++) {
            for (int u = 0; u < n; u++) {
                for (auto& e : adj[u]) {
                    if (dist[u] != INF && dist[u] + e.w < dist[e.v]) {
                        dist[e.v] = dist[u] + e.w;
                    }
                }
            }
        }

        for (int u = 0; u < n; u++) {
            for (const auto& e : adj[u]) {
                if (dist[u] != INF && dist[u] + e.w < dist[e.v]) {
                    if (!mark[u]) dfs(u);
                }
            }
        }
    }

    void dfs(int u) {
        mark[u] = true;
        for (auto& e : adj[u]) {
            if (!mark[e.v]) dfs(e.v);
        }
    }
};

struct Solution {
    Solution() {
        int n, m;
        cin >> n >> m;

        Graph g(n);

        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            g.addEdge(u, v, -w);
        }

        g.runBellmanFord(0);

        cout << (g.mark[n - 1] ? -1 : -g.dist[n - 1]) << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution();

    return 0;
}
