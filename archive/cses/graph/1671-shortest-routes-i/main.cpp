#include <bits/stdc++.h>

using namespace std;

const int64_t INF = 1e18;

struct Edge {
    int v, w;
    Edge(int v_, int w_) : v(v_), w(w_) {}
};

struct Node {
    int u;
    int64_t d;
    Node(int u_, int64_t d_) : u(u_), d(d_) {}
    bool operator<(const Node& o) const {
        return d > o.d;
    }
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

    void runDijkstra(int s) {
        fill(dist.begin(), dist.end(), INF);
        fill(mark.begin(), mark.end(), false);
        priority_queue<Node> pq;

        dist[s] = 0;
        pq.emplace(s, 0);

        while (!pq.empty()) {
            Node top = pq.top();
            pq.pop();

            int u = top.u;
            if (dist[u] < top.d) continue;

            for (auto& e : adj[u]) {
                if (dist[u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[u] + e.w;
                    pq.emplace(e.v, dist[e.v]);
                }
            }
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
            g.addEdge(u, v, w);
        }

        g.runDijkstra(0);

        for (int u = 0; u < n; u++) {
            cout << g.dist[u] << ' ';
        }
        cout << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution();

    return 0;
}
