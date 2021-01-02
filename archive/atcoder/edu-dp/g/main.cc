#include <bits/stdc++.h>

using namespace std;

template <typename T> void minimize(T& a, T b) { a = min(a, b); }
template <typename T> void maximize(T& a, T b) { a = max(a, b); }

template <typename T>
class vec2d : public vector<vector<T>> {
public:
    vec2d(int n=0, int m=0, T t=T())
        : vector<vector<T>>(n, vector<T>(m, t)) {}
};

struct Solver {
    int n, m;
    vec2d<int> adj;
    vector<int> visited;
    vector<int> order;

    Solver() {
        cin >> n >> m;
        adj.resize(n);
        visited.assign(n, 0);

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
        }
    }

    void dfs(int u) {
        visited[u]++;

        for (int v : adj[u]) {
            assert(visited[v] != 1); // acyclic
            if (!visited[v]) dfs(v);
        }

        visited[u]++;
        order.push_back(u);
    }

    void topoSort() {
        for (int u = 0; u < n; u++) {
            if (!visited[u]) dfs(u);
        }
        reverse(order.begin(), order.end());
    }

    int solve() {
        topoSort();
        vector<int> dp(n, 0);
        // dp[u]: longest path ending at node u in the graph

        int ans = 0;

        for (int u : order) {
            for (int v : adj[u]) {
                maximize(dp[v], dp[u] + 1);
                maximize(ans, dp[v]);
            }
        }

        return ans;
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solver solver;
    cout << solver.solve() << '\n';

    return 0;
}
