#include <bits/stdc++.h>

using namespace std;

template <typename T>
void umin(T& a, const T& b) { a = min(a, b); }
template <typename T>
void umax(T& a, const T& b) { a = max(a, b); }

const int64_t INF = 1e18;

struct Solution {
    Solution() {
        int n, m, q;
        cin >> n >> m >> q;

        vector<vector<int64_t>> g(n, vector<int64_t>(n));

        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                g[u][v] = (u == v) ? 0 : INF;
            }
        }

        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            umin(g[u][v], (int64_t) w);
            umin(g[v][u], (int64_t) w);
        }

        for (int k = 0; k < n; k++) {
            for (int u = 0; u < n; u++) {
                for (int v = 0; v < n; v++) {
                    if (g[u][k] != INF && g[k][v] != INF) {
                        umin(g[u][v], g[u][k] + g[k][v]);
                    }
                }
            }
        }

        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            cout << (g[u][v] == INF ? -1 : g[u][v]) << '\n';
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution();

    return 0;
}
