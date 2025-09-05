#include <bits/stdc++.h>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...) 42
#endif

using namespace std;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

struct Coor {
    int x, y;

    Coor(int x_, int y_) : x(x_), y(y_) {}

    int64_t ManhattanDist(const Coor& other) const {
        return 1LL * abs(x - other.x) + abs(y - other.y);
    }
};

struct Edge {
    int v;
    int w;

    Edge(int v_, int w_) : v(v_), w(w_) {}
};

struct PQEntry {
    int u;
    int64_t d;
    int64_t f;

    // PQEntry(int u_, int64_t d_) : u(u_), d(d_) {}
    PQEntry(int u_, int64_t d_, int64_t f_) : u(u_), d(d_), f(f_) {}

    // bool operator>(const PQEntry& other) const { return d > other.d; }
    bool operator>(const PQEntry& other) const { return f > other.f; }
};

struct Graph {
    int n;
    int w_max;
    vector<vector<Edge>> adj;
    int edgecnt;

    Graph(int n_, int w_max_) : n(n_), w_max(w_max_), adj(n_), edgecnt(0) {}

    void AddEdge(int u, int v, int w) {
        edgecnt++;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void AddEdgeWithManhattanDistance(int u, int v, const vector<Coor>& coors) {
        int w = coors[u].ManhattanDist(coors[v]);
        if (w <= w_max) {
            AddEdge(u, v, w);
            AddEdge(v, u, w);
        }
    }

    int Dijkstra(int s, int t, vector<int64_t>& h) {
        dbg(w_max);
        dbg(edgecnt);
        vector<int64_t> dist(n, 1e18);
        MinHeap<PQEntry> pq;
        dist[s] = 0;
        pq.emplace(s, 0, 0);

        while (!pq.empty()) {
            PQEntry cur = pq.top();
            pq.pop();

            int u = cur.u;
            int64_t d = cur.d;

            if (u == t) return d;
            if (dist[u] < d) continue;

            for (Edge& e : adj[u]) {
                int v = e.v;
                int w = e.w;

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.emplace(v, dist[v], dist[v] + h[v]);
                }
            }
        }

        assert(false);
    }
};

int main() {
    int sx, sy;
    cin >> sx >> sy;
    int tx, ty;
    cin >> tx >> ty;

    int n;
    cin >> n;

    int s = 0;
    int t = 2 * n + 1;

    vector<Coor> coors;

    coors.emplace_back(sx, sy);
    for (int i = 0; i < 2 * n; i++) {
        int x;
        int y;
        cin >> x >> y;
        coors.emplace_back(x, y);
    }
    coors.emplace_back(tx, ty);

    int64_t w_max = coors[s].ManhattanDist(coors[t]);

    for (int i = 0; i < n; i++) {
        int p = 2 * i + 1;
        int q = 2 * i + 2;
        w_max = min(w_max, coors[s].ManhattanDist(coors[p]) +
                               coors[t].ManhattanDist(coors[q]) + 1);
        w_max = min(w_max, coors[s].ManhattanDist(coors[q]) +
                               coors[t].ManhattanDist(coors[p]) + 1);
    }

    Graph g(2 * n + 2, w_max);

    g.AddEdgeWithManhattanDistance(s, t, coors);

    for (int i = 0; i < n; i++) {
        g.AddEdgeWithManhattanDistance(s, 2 * i + 1, coors);
        g.AddEdgeWithManhattanDistance(s, 2 * i + 2, coors);
        g.AddEdgeWithManhattanDistance(t, 2 * i + 1, coors);
        g.AddEdgeWithManhattanDistance(t, 2 * i + 2, coors);
    }

    for (int i = 0; i < n; i++) {
        g.AddEdge(2 * i + 1, 2 * i + 2, 1);
    }

    for (int i = 1; i <= 2 * n; i += 2) {
        for (int j = i + 2; j <= 2 * n; j++) {
            g.AddEdgeWithManhattanDistance(i, j, coors);
            g.AddEdgeWithManhattanDistance(i + 1, j, coors);
        }
    }

    vector<int64_t> h(2 * n + 2);
    fill(h.begin() + 1, h.begin() + 2 * n + 1, 1e18);
    h[s] = 0;
    h[t] = 0;

    for (int i = 1; i <= 2 * n; i += 2) {
        int i1 = i;
        int i2 = i + 1;
        int64_t min_d = 1e18;

        for (int j = i + 2; j <= 2 * n; j += 2) {
            int j1 = j;
            int j2 = j + 1;

            min_d = min(min_d, coors[i1].ManhattanDist(coors[j1]));
            min_d = min(min_d, coors[i2].ManhattanDist(coors[j1]));
            min_d = min(min_d, coors[i1].ManhattanDist(coors[j2]));
            min_d = min(min_d, coors[i2].ManhattanDist(coors[j2]));

            h[i1] = min(h[i1], min_d);
            h[i2] = min(h[i2], min_d);
            h[j1] = min(h[j1], min_d);
            h[j2] = min(h[j2], min_d);
        }

        min_d = min(min_d, coors[i1].ManhattanDist(coors[t]));
        min_d = min(min_d, coors[i2].ManhattanDist(coors[t]));
        h[i1] = min(h[i1], min_d);
        h[i2] = min(h[i2], min_d);
    }

    cout << g.Dijkstra(s, t, h) << '\n';

    return 0;
}
