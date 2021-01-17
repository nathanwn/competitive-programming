struct Graph {
    int n, m;
    vector<vector<int>> adj;
    vector<vector<int>> adj_t;
    vector<int> order;
    vector<int> mark;
    vector<int> leaders;
    vector<vector<int>> components;

    void reverseGraph() {
        for (int u = 0; u < n; u++) {
            for (int &v : adj[u]) {
                adj_t[v].push_back(u);
            }
        }
    }

    void dfsForward(int u) {
        assert(mark[u] == 0);
        mark[u] = 1;

        for (int &v : adj[u]) {
            if (mark[v] == 0) {
                dfsForward(v);
            }
        }

        order.push_back(u);
    }

    void dfsBackward(int u, int leader, vector<int> &component) {
        assert(mark[u] == 1);
        mark[u] = 0;
        leaders[u] = leader;
        component.push_back(u);

        for (int &v : adj_t[u]) {
            if (mark[v] == 1) {
                dfsBackward(v, leader, component);
            }
        }
    }

    void scc() { // Kosaraju's algorithm
        fill(mark, mark + n, 0);
        for (int u = 0; u < n; u++) {
            if (mark[u] == 0) {
                dfsForward(u);
            }
        }

        reverseGraph();

        reverse(order.begin(), order.end());

        for (int u : order) {
            if (mark[u] == 1) {
                vector<int> component;
                dfsBackward(u, u, component);
                components.emplace_back(component);
            }
        }
    }
};
