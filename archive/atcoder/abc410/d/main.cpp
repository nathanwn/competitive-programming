#include <iostream>
#include <vector>
#include <queue>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;


struct Graph {
    int n;
    vector<vector<pair<int, int>>> adj;

    Graph(int n_) : n(n_), adj(n_) {}

    void add_edge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
    }

    int solve() {
        const int MAX = (1 << 10) + 1;
        int s = 0;
        int t = n - 1;

        vector<vector<int>> visited(n, vector<int>(MAX));
        queue<pair<int, int>> q;

        visited[s][0] = true;
        q.emplace(s, 0);

        while (!q.empty()) {
            auto [u, val] = q.front(); q.pop();
            for (auto [v, w] : adj[u]) {
                int new_val = val ^ w;
                if (visited[v][new_val]) {
                    continue;
                }
                visited[v][new_val] = true;
                q.emplace(v, new_val);
            }
        }
        for (int val = 0; val < MAX; val++) {
            if (visited[t][val]) {
                return val;
            }
        }
        return -1;
    }
};

struct Solver {
    Solver(istream& in, ostream& out) {
        int n, m;
        in >> n >> m;
        Graph g(n);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            in >> u >> v >> w;
            u--; v--;
            g.add_edge(u, v, w);
        }
        out << g.solve() << "\n";
    }
};

int main() {
    Solver solver(cin, cout);
    return 0;
}
