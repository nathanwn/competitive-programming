#include <bits/stdc++.h>

using namespace std;

template <typename T> T min(T a, T b, T c) { return min(min(a, b), c); }

const int inf = (int) 1e9;

struct Solver {

    Solver() {
        int n, m;
        cin >> n >> m;

        vector<string> s(n);

        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }

        vector<vector<int>> h(n, vector<int>(m, 0));
        // h[i][j]: height of the largest tree starting from (i, j)
        //
        int64_t ans = 0;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < m; j++) {
                if (i == n - 1) {
                    if (s[i][j] == '*') {
                        h[i][j] = 1;
                    }
                } else {
                    if (j == 0 || j == m - 1) {
                        if (s[i][j] == '*') {
                            h[i][j] = 1;
                        }
                    } else {
                        if (s[i][j] == '*') {
                            h[i][j] = min(
                                    h[i + 1][j - 1],
                                    h[i + 1][j],
                                    h[i + 1][j + 1]) + 1;
                        }
                    }
                }
                ans += h[i][j];
            }
        }

        cout << ans << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        Solver solver;
    }

    return 0;
}
