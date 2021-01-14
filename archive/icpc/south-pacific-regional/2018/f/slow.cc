#include <bits/stdc++.h>

using namespace std;

const int64_t inf = 1e18;

template <typename T>
class vec2d : public vector<vector<T>> {
public:
    vec2d(int n=0, int m=0, T t=T())
        : vector<vector<T>>(n, vector<T>(m, t)) {}
};

int main() {
    int n, m;
    cin >> n >> m;
    vec2d<int64_t> g(n, n, inf);
    vec2d<int64_t> g0(n, n, inf);
    vec2d<int64_t> gp(n, n, inf);

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            int w;
            cin >> w;
            g[u][v] = g0[u][v] = w;
        }
    }

    int path_length = 0;

    while (true) {
        int stop = true;
        for (int v = 0; v < n; v++) {
            if (g[0][v] <= m) stop = false;
        }

        if (stop) break;

        path_length++;

        swap(g, gp);

        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                g[u][v] = inf;

                for (int k = 0; k < n; k++) {
                    g[u][v] = min(g[u][v], gp[u][k] + g0[k][v]);
                }
            }
        }
    }

    cout << path_length << '\n';

    return 0;
}
