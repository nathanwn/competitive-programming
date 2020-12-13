#include <bits/stdc++.h>

using namespace std;

template <typename T> void UpdateMin(T& a, T b) { a = min(a, b); }
template <typename T> void UpdateMax(T& a, T b) { a = max(a, b); }

struct Edge {
    int from;
    int to;
    int weight;

    Edge() :
        from(0), to(0), weight(0) {}

    Edge(int from, int to, int weight) :
        from(from), to(to), weight(weight) {}
};

struct PQElem {
    int node;
    int dist;

    PQElem(int node, int dist) : node(node), dist(dist) {}

    bool operator<(const PQElem& other) const {
        return dist > other.dist;
    }
};

struct ShortestPath {
    int length;
    vector<Edge> path;
};

struct Solver {
    const int inf = (int) 1e9;
    int n, m, s, t;
    vector<vector<Edge>> adj;
    pair<int, int> removed = {-1, -1};

    Solver(int n, int m, int s, int t) : n(n), m(m), s(s - 1), t(t - 1) {
        adj.resize(n);

        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            adj[u].emplace_back(u, v, w);
            adj[v].emplace_back(v, u, w);
        }

        ShortestPath best_path = doDijkstra();

        int min_second_best_path_length = inf;

        for (Edge& e : best_path.path) {
            int u = e.from;
            int v = e.to;

            removed = {u, v};

            ShortestPath second_best_path = doDijkstra();
            UpdateMin(min_second_best_path_length, second_best_path.length);
        }

        if (min_second_best_path_length == inf) {
            cout << "Matt wins.\n";
        } else {
            cout << (min_second_best_path_length - best_path.length) << "\n";
        }
    }

    ShortestPath doDijkstra() {
        vector<int> d(n, inf); // distance from source
        unordered_map<int, Edge> relax_edge;
        priority_queue<PQElem> pq;

        d[s] = 0;
        pq.emplace(s, 0);

        while (!pq.empty()) {
            PQElem top = pq.top();
            pq.pop();
            int u = top.node;

            if (top.dist > d[u]) {
                continue;
            }

            for (Edge& e : adj[u]) {
                int v = e.to;
                int w = e.weight;

                if ((u == removed.first && v == removed.second) ||
                    (v == removed.first && u == removed.second)) {
                    continue;
                }

                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    relax_edge[v] = e;
                    pq.emplace(v, d[v]);
                }
            }
        }

        ShortestPath res;
        res.length = d[t];

        if (d[t] == inf) {
            return res;
        }

        for (int v = t; v != s; v = relax_edge[v].from) {
            res.path.push_back(relax_edge[v]);
        }

        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n, m, s, t;
        cin >> n >> m >> s >> t;

        if (n == 0 && m == 0) break;

        Solver(n, m, s, t);
    }

    return 0;
}
