#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int u, v, h, w;
    Edge(int u_, int v_, int h_, int w_) : u(u_), v(v_), h(h_), w(w_) {}
};

struct Node {
    int u;
    int64_t d;

    Node(int u_, int64_t d_) : u(u_), d(d_) {}

    bool operator<(const Node& other) const {
        return d > other.d; // min-heap
    }
};

struct Graph {
    const int64_t inf = 1e18;

    int n;
    vector<vector<Edge>> adj;
    vector<int64_t> dist;

    Graph(int n_) : n(n_), adj(n), dist(n) {}

    void addEdge(int u, int v, int h, int w) {
        adj[u].emplace_back(u, v, h, w);
        adj[v].emplace_back(v, u, h, w);
    }

    int64_t dijkstra(int src, int sink, int hlimit) {
        fill(dist.begin(), dist.end(), inf);

        priority_queue<Node> pq;

        pq.emplace(src, 0);
        dist[src] = 0;

        while (!pq.empty()) {
            Node cur = pq.top();
            pq.pop();

            int u = cur.u;

            if (u == sink) return dist[u];
            if (dist[u] < cur.d) continue;

            for (const Edge& e : adj[u]) {
                if (e.h > hlimit) continue;
                if (dist[u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[u] + e.w;
                    pq.emplace(e.v, dist[e.v]);
                }
            }
        }

        return inf;
    }

    pair<int, int64_t> solve(int src, int sink, int from, int to) {
        int64_t ans = inf;

        while (from <= to) {
            int mid = from + (to - from) / 2;
            int64_t res = dijkstra(src, sink, mid);

            if (res == inf) {
                from = mid + 1;
            } else {
                ans = res;
                to = mid - 1;
            }
        }

        assert(ans != inf);
        return make_pair(from, ans);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, e;
    cin >> n >> m >> s >> e;
    s--, e--;

    Graph g(n);

    int from = 0;
    int to = -1;

    for (int i = 0; i < m; i++) {
        int u, v, h, w;
        cin >> u >> v >> h >> w;
        u--, v--;
        g.addEdge(u, v, h, w);
        to = max(to, h);
    }

    pair<int, int64_t> ans =  g.solve(s, e, from, to);
    cout << ans.first << "\n" << ans.second << "\n";

    return 0;
}
