#include <bits/stdc++.h>

using namespace std;

const int64_t inf = (1LL << 62);

int64_t ceilDiv(int64_t a, int64_t x) {
    return (a + x - 1) / x;
}

struct Edge {
    int v, w;
    Edge(int v_, int w_) : v(v_), w(w_) {}
};

struct Node {
    int u;
    int64_t d;
    Node(int u_, int64_t d_) : u(u_), d(d_) {}

    bool operator<(const Node& other) const {
        return d > other.d;
    }
};

struct DiGraph {
    int n;
    vector<vector<Edge>> adj;
    vector<vector<int64_t>> d;

    DiGraph(int n_) :
        n(n_), adj(n_ + 1), d(n_ + 1, vector<int64_t>(n_ + 1, inf)) {}

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
    }

    int64_t solve() {
        // Add a new node to the graph
        for (int v = 0; v < n; v++) {
            addEdge(n, v, 0);
        }

        // Bellman-Ford
        d[n][n] = 0;

        for (int i = 0; i < n; i++) {
            int relaxed = false;

            for (int u = n; u >= 0; u--) {                 
                // It's a bit more clever if we try to relax
                // from n first since it is the source node
                for (Edge& e : adj[u]) {
                    int v = e.v, w = e.w;
                    if (d[n][u] != inf && d[n][u] + w < d[n][v]) {
                        d[n][v] = d[n][u] + w;
                        relaxed = true;
                    }
                }
            }

            if (!relaxed) break;
        }

        // Modify weights
        for (int u = 0; u < n; u++) {
            for (Edge& e : adj[u]) {
                int v = e.v;
                e.w += d[n][u] - d[n][v];
            }
        }

        // Dijkstra
        for (int s = 0; s < n; s++) {
            priority_queue<Node> q;
            d[s][s] = 0;
            q.emplace(s, 0);

            while (q.size() > 0) {
                Node node = q.top(); q.pop();
                int u = node.u;
                if (node.d > d[s][u]) continue;

                for (Edge& e : adj[u]) {
                    int v = e.v, w = e.w;
                    if (d[s][u] + w < d[s][v]) {
                        d[s][v] = d[s][u] + w;
                        q.emplace(v, d[s][v]);
                    }
                }
            }
        }

        int64_t sum = 0;

        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (u == v) continue;
                d[u][v] += d[n][v] - d[n][u];
                sum += d[u][v];
            }
        }

        int64_t avg = ceilDiv(sum, n * (n - 1));
        return avg;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;

    int n = h * w;

    auto cell = [&](int i, int j) {
        if (i < 0 || i >= h) return -1;
        if (j < 0 || j >= w) return -1;
        return i * w + j;
    };
    
    auto west = [&](int i, int j) { return cell(i, j - 1); };
    auto east = [&](int i, int j) { return cell(i, j + 1); };
    auto north = [&](int i, int j) { return cell(i - 1, j); };
    auto south = [&](int i, int j) { return cell(i + 1, j); };

    DiGraph g(n);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int c;
            cin >> c;
            int u = cell(i, j);
            int v = north(i, j);
            if (v != -1) g.addEdge(u, v, c);
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int c;
            cin >> c;
            int u = cell(i, j);
            int v = west(i, j);
            if (v != -1) g.addEdge(u, v, c);
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int c;
            cin >> c;
            int u = cell(i, j);
            int v = south(i, j);
            if (v != -1) g.addEdge(u, v, c);
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int c;
            cin >> c;
            int u = cell(i, j);
            int v = east(i, j);
            if (v != -1) g.addEdge(u, v, c);
        }
    }

    int64_t ans = g.solve();

    cout << ans << '\n';

    return 0;
}
