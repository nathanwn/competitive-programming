#include <functional>
#include <iostream>
#include <vector>

using namespace std;

vector<int> topo_sort(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> mark(n, 0);
    vector<int> order;
    bool has_cycle = false;

    function<void(int)> dfs = [&](int u) {
        mark[u] = 1;

        for (int v : adj[u]) {
            if (mark[v] == 1) {
                has_cycle = true;
            } else if (mark[v] == 0) {
                dfs(v);
            }
        }

        mark[u] = 2;
        order.push_back(u);
    };

    for (int u = 0; u < n; u++) {
        if (mark[u] == 0) dfs(u);
    }

    if (has_cycle) return vector<int>();

    reverse(order.begin(), order.end());
    return order;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }

    vector<int> order = topo_sort(adj);

    if (order.size() == 0) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < (int) order.size(); i++) {
            cout << (order[i] + 1) << " \n"[i == (int) order.size() - 1];
        }
    }
    return 0;
}
