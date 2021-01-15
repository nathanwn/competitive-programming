#include <bits/stdc++.h>

using namespace std;

/**
 * We can use matrix to calculate the shortest path of length k between any pair
 * of vertices in the graph. For more details, refer to page 222 of the CSES book.
 *
 * Time complexity of this solution: O(n^3 * m) where n <= 100 and m <= 10^9
 * which is a bit too slow.
 *
 * Can be further optimized using binary search + a technique which is similar to
 * binary exponentiation.
**/

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
    vec2d<int64_t> g1(n, n, inf);
    vec2d<int64_t> prev_g(n, n, inf);

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            int w;
            cin >> w;
            g[u][v] = g1[u][v] = w;
        }
    }

    int path_length = 0;

    while (true) {
        int64_t min_cost = inf;
        int stop = true;

        for (int v = 0; v < n; v++) {
            min_cost = min(min_cost, g[0][v]);
        }

        if (min_cost > m) break;

        path_length++;

        swap(g, prev_g);

        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                g[u][v] = inf;

                for (int k = 0; k < n; k++) {
                    g[u][v] = min(g[u][v], prev_g[u][k] + g1[k][v]);
                }
            }
        }
    }

    cout << path_length << '\n';

    return 0;
}
