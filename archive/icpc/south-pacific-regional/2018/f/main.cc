#include <bits/stdc++.h>

using namespace std;

/**
 * Time complexity: O(n^3 * log^2(m)), where n <= 100 and m <= 10^9
 *
 * I think it can be further optimized a bit more (I'm not quite sure, and also
 * don't really feel like doing it). This is good enough to get AC anyway.
**/

template <typename T>
struct vec2d : public vector<vector<T>> {
    vec2d(int n=0, int m=0, T t=T())
        : vector<vector<T>>(n, vector<T>(m, t)) {}
};

const int64_t inf = 1e18;

struct Solver {
    int n, m;
    vec2d<int64_t> g;

    void combine(vec2d<int64_t>& c, vec2d<int64_t>& a, vec2d<int64_t>& b) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                c[u][v] = inf;
                for (int k = 0; k < n; k++) {
                    c[u][v] = min(c[u][v], a[u][k] + b[k][v]);
                }
            }
        }
    }

    void print(const vec2d<int64_t>& x) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (x[i][j] == inf) cout << "inf ";
                else cout << x[i][j] << ' ';
            }
            cout << '\n';
        }
    }


    bool possible(int limit) {
        vec2d<int64_t> gp(n, n, inf);
        vec2d<int64_t> prev_gp(n, n, inf);
        vec2d<int64_t> res(n, n, inf);
        vec2d<int64_t> prev_res(n, n, inf);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = gp[i][j] = g[i][j];
            }
        }

        int cnt = 1;

        // I don't really know how to define res^0, so yeah...
        limit--;

        while (limit > 0) {
            if (limit & 1) {
                swap(res, prev_res);
                combine(res, prev_res, gp);
            }
            swap(gp, prev_gp);
            combine(gp, prev_gp, prev_gp);
            cnt <<= 1;
            limit >>= 1;
        }

        int64_t min_cost = inf;

        for (int j = 0; j < n; j++) {
            min_cost = min(min_cost, res[0][j]);
        }

        return min_cost <= m;
    }

    Solver() {
        cin >> n >> m;
        g = vec2d<int64_t>(n, n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> g[i][j];
            }
        }

        int from = 0;
        int to = m;

        int ans = 0;

        while (from <= to) {
            int mid = from + (to - from) / 2; // maximum legs allowed
            if (possible(mid)) {
                ans = mid;
                from = mid + 1;
            } else {
                to = mid - 1;
            }
        }

        cout << ans << '\n';
    }
};

int main() {
    Solver solver;
    return 0;
}
