#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int MOD = 998244353;

void add(int& a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

struct Graph {
    int n;
    vector<vector<int>> children;
    vector<int> val;
    vector<int64_t> inherit;

    Graph(int n_) : n(n_), children(n_), val(n_), inherit(n_, 0) {}

    void addEdge(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        children[u].push_back(v);
    }

    int64_t total(int u) {
        return inherit[u] + val[u];
    }
};

struct TopoSort {
    Graph g;
    vector<int> order;
    vector<int> mark;

    TopoSort(const Graph& g_) : g(g_) {
        order.resize(g.n);
        mark.resize(g.n, 0);
        for (int u = 0; u < g.n; u++) {
            if (!mark[u]) dfs(u);
        }
        reverse(order.begin(), order.end());
    }

    void dfs(int u) {
        mark[u] = 1;
        for (int v : g.children[u]) {
            if (!mark[v]) {
                dfs(v);
            }
        }
        order.push_back(u);
    }
};

struct Solver {
    Solver() {
        int n, m;
        cin >> n >> m;
        Graph g(n);

        for (int i = 0; i < n; i++) cin >> g.val[i];

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            g.addEdge(u, v);
        }

        const vector<int>& topo_order = TopoSort(g).order;
        int64_t ans = 0;

        for (int u : topo_order) {
            // cerr << "u = " << u << '\n';
            for (int x = 0; x < g.n; x++) {
                // cerr << g.val[x] << " \n"[x == g.n - 1];
            }
            if (g.children[u].size() == 0) { // leaf
                ans = max(ans, g.total(u));
            } else {
                for (int v : g.children[u]) {
                    int64_t from_u = g.total(u);
                    if (from_u > 0 && g.val[v] == 0) {
                        from_u++;
                    }
                    g.inherit[v] = max(g.inherit[v], from_u);
                }
            }
            for (int x = 0; x < g.n; x++) {
                // cerr << g.val[x] << " \n"[x == g.n - 1];
            }
        }

        cout << (ans % MOD) << '\n';
    }
};

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        Solver();
    }
    return 0;
}
