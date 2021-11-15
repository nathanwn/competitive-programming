#include <bits/stdc++.h>

using namespace std;

struct Graph {
    int n;
    vector<vector<int>> adj;
    vector<int> descendants;

    Graph(int n_) : n(n_), adj(n), descendants(n, 0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u) {
        for (int v : adj[u]) {
            dfs(v);
            descendants[u] += descendants[v];
        }
        descendants[u] += adj[u].size();
    }
};

struct Solver {
    Solver() {
        int n;
        cin >> n;
        Graph g(n);
        for (int u = 1; u < n; u++) {
            int p; cin >> p; p--;
            g.addEdge(p, u);
        }
        g.dfs(0);
        for (int u = 0; u < n; u++) {
            cout << g.descendants[u] << ' ';
        }
        cout << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    Solver s;
    return 0;
}
