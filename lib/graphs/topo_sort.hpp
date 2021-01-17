struct Graph {
    int n, m;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<int> topo_order;

    void dfs(int u) {
        visited[u] = true;

        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }

        topo_order.push_back(u);
    }

    void topoSort() {
        fill(visited.begin(), visited.end(), false);

        for (int u = 0; u < n; u++) {
            if (!visited[u]) {
                dfs(u);
            }
        }

        reverse(topo_order.begin(), topo_order.end());
    }
};
