#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

struct Graph {
    struct Edge {
        int v;
        int w;
    };

    struct Node {
        int u;
        int c;

        bool operator<(const Node& other) const {
            return c > other.c;
        }
    };

    int n;
    vector<vector<Edge>> adj;
    vector<vector<int>> cap;

    Graph(int n_) : n(n_), adj(n), cap(n, vector<int>(n, inf)) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dijkstra(int s) {
        priority_queue<Node> q;
        cap[s][s] = 0;
        q.push({s, 0});

        while (!q.empty()) {
            Node top = q.top();
            q.pop();
            int u = top.u;

            if (cap[s][u] < top.c) continue;

            for (const Edge& e : adj[u]) {
                int v = e.v;
                int w = e.w;
                if (max(cap[s][u], w) < cap[s][v]) {
                    cap[s][v] = max(cap[s][u], w);
                    q.push({v, cap[s][v]});
                }
            }
        }
    }

    void solve() {
        for (int u = 0; u < n; u++) {
            dijkstra(u);
        }
    }

    int answer(int u, int v) {
        return cap[u][v];
    }
};

struct Solver {
    int n, m, q;

    Solver(int n_, int m_, int q_) : n(n_), m(m_), q(q_) {
        Graph g(n);

        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            g.addEdge(u, v, w);
        }

        g.solve();

        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            int cap = g.answer(u, v);
            if (cap == inf) {
                cout << "no path\n";
            } else {
                cout << cap << '\n';
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test_id = 1;

    while (true) {
        int n, m, q;
        cin >> n >> m >> q;
        if (n == 0 && m == 0 && q == 0) break;
        if (test_id > 1) cout << '\n';
        cout << "Case #" << test_id++ << '\n';
        Solver solver(n, m, q);
    }

    return 0;
}
