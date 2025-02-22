#include <iostream>
#include <vector>
#include <queue>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

const int INF = (int) 1e9;

struct PalinPath {
    int u;
    int v;

    PalinPath(int u_, int v_) : u(u_), v(v_) {}
};

int main() {
    int n;
    cin >> n;

    vector<string> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    vector<vector<int>> d(n, vector<int>(n, INF));
    queue<PalinPath> q;
    // Note: It is important to populate the queue with all paths with length 0
    // before paths of length 1.
    for (int u = 0; u < n; u++) {
        d[u][u] = 0;
        q.emplace(u, u);
    }
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u != v && c[u][v] != '-') {
                d[u][v] = 1;
                q.emplace(u, v);
            }
        }
    }

    while (!q.empty()) {
        PalinPath path = q.front(); q.pop();
        int u1 = path.u;
        int v1 = path.v;
        for (int u2 = 0; u2 < n; u2++) {
            for (int v2 = 0; v2 < n; v2++) {
                if (d[u2][v2] == INF && c[u2][u1] == c[v1][v2] && c[u2][u1] != '-') {
                    d[u2][v2] = d[u1][v1] + 2;
                    q.emplace(u2, v2);
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (v != 0) cout << " ";
            if (d[u][v] == INF) cout << "-1";
            else cout << d[u][v];
        }
        cout << "\n";
    }

    return 0;
}
