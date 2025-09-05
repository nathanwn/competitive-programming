#include <bits/stdc++.h>

using namespace std;

struct Intersection {
    int r, c;
    Intersection(int r_, int c_) : r(r_), c(c_) {}
    bool operator<(const Intersection& o) const {
        if (r == o.r) return c < o.c;
        else return r < o.r;
    }
};

struct Edge {
    int u, v;
    bool operator<(const Edge& o) const {
        if (u == o.u) return v < o.v;
        else return u < o.u;
    }
};

struct Graph {
    vector<vector<int>> adj;
    set<Edge> visited;
    map<Intersection, int> id;
    int ans = 0;

    void go(int u, int len) {
        ans = max(ans, len);

        for (int v : adj[u]) {
            if (visited.find({u, v}) != visited.end() ||
                visited.find({v, u}) != visited.end()) continue;
            visited.insert({u, v});
            go(v, len + 1);
            visited.erase({u, v});
        }
    }

    void connect(int i1, int j1, int i2, int j2) {
        Intersection x(i1, j1);
        Intersection y(i2, j2);
        if (id.find(x) == id.end()) {
            id.emplace(x, id.size());
            adj.push_back(vector<int>());
        }
        if (id.find(y) == id.end()) {
            id.emplace(y, id.size());
            adj.push_back(vector<int>());
        }
        int u = id[x];
        int v = id[y];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int solve() {
        int n = id.size();

        for (int u = 0; u < n; u++) {
            go(u, 0);
        }

        return ans;
    }
};

struct Solver {
    vector<string> b;
    vector<Graph> g;

    Solver() {
        g.resize(3);
        string row;

        while (cin >> row) {
            b.push_back(row);
        }

        int nr = b.size();
        int nc = b[0].size();

        /**
         * If you look closely, you can see that the lane network is formed
         * with the following shape:
         *      \
         *       \
         *        >------
         *       /
         *      /
        **/

        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                if (b[i][j] == '>') {
                    if (i - 3 >= 0 && j - 3 >= 0 && b[i - 3][j - 3] == '<') {
                        char c = b[i - 1][j - 1];
                        if (c != '\\') {
                            int p = c - '1';
                            assert(0 <= p && p < 3);
                            g[p].connect(i, j, i - 3, j - 3);
                        }
                    }
                    if (i + 3 < nr && j - 3 >= 0 && b[i + 3][j - 3] == '<') {
                        char c = b[i + 1][j - 1];
                        if (c != '/') {
                            int p = c - '1';
                            assert(0 <= p && p < 3);
                            g[p].connect(i, j, i + 3, j - 3);
                        }
                    }
                    if (j + 6 < nc && b[i][j + 6] == '<') {
                        char c = b[i][j + 1];
                        if (c != '-') {
                            int p = c - '1';
                            assert(0 <= p && p < 3);
                            g[p].connect(i, j, i, j + 6);
                        }
                    }
                }
            }
        }

        for (int p = 0; p < 3; p++) {
            cout << g[p].solve() << ' ';
        }
        cout << '\n';
    }
};

int main() {
    Solver solver;
    return 0;
}
