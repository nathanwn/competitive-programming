#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int n;
    vector<int> p;
    vector<int> d;

    DSU(int n) : n(n) {
        p.resize(n);
        d.resize(n, 0);
        for (int i = 0; i < n; i++) p[i] = i;
    }

    int get(int u) {
        while (u != p[u]) u = p[u];
        return u;
    }

    bool merge(int u, int v) {
        u = get(u), v = get(v);
        if (u == v) return false;

        if (d[u] > d[v]) {
            p[v] = u;
        } else {
            p[u] = v;
            if (d[u] == d[v]) d[v]++;
        }
        return true;
    }
};

struct Solver {
    int n, m;

    Solver(int n, int m) : n(n), m(m) {
        vector<vector<int>> tree1 = readTree(n);
        vector<vector<int>> tree2 = readTree(m);

        if (check(tree1, tree2))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    bool check(vector<vector<int>>& tree1, vector<vector<int>>& tree2) {
        DSU dsu(n + m);

        if (tree1.size() == 0 && tree2.size() == 0) {
            return true;
        } else if ((tree1.size() == 0 && tree2.size() != 0)
                || (tree1.size() != 0 && tree2.size() == 0)) {
            return false;
        }

        queue<pair<int, int>> q;
        q.push({0, 0});

        while (!q.empty()) {
            int u = q.front().first;
            int v = q.front().second;
            q.pop();

            if (dsu.get(u) == dsu.get(v + n)) continue;

            if (tree1[u].size() != tree2[v].size()) {
                return false;
            }

            dsu.merge(u, v + n);

            for (int i = 0; i < (int) tree1[u].size(); i++) {
                q.push({tree1[u][i], tree2[v][i]});
            }
        }

        return true;
    }

    vector<vector<int>> readTree(int n_nodes) {
        vector<vector<int>> tree(n_nodes);

        for (int u = 0; u < n_nodes; u++) {
            int n_adj;
            cin >> n_adj;

            for (int i = 0; i < n_adj; i++) {
                int v;
                cin >> v;
                tree[u].push_back(v);
            }
        }

        return tree;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n, m;
        cin >> n >> m;

        if (n == 0 && m == 0) break;

        Solver(n, m);
    }

    return 0;
}
