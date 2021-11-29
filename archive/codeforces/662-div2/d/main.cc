#include <bits/stdc++.h>

using namespace std;

template <typename T> void minimize(T& a, T b) { a = min(a, b); }
template <typename T> void maximize(T& a, T b) { a = max(a, b); }

const int inf = (int) 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    // dp[i][j]: size of rhombus starting (downwards) at cell (i, j)
    vector<vector<int>> dp(n, vector<int>(m));
    int ans = 0;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            if (i >= n - 2 || j == 0 || j == m - 1) {
                dp[i][j] = 1;
            } else {
                if (grid[i][j] == grid[i + 1][j - 1]
                        && grid[i][j] == grid[i + 1][j]
                        && grid[i][j] == grid[i + 1][j + 1]
                        && grid[i][j] == grid[i + 2][j]) {
                    dp[i][j] = inf;
                    minimize(dp[i][j], dp[i + 1][j - 1] + 1);
                    minimize(dp[i][j], dp[i + 1][j] + 1);
                    minimize(dp[i][j], dp[i + 1][j + 1] + 1);
                    minimize(dp[i][j], dp[i + 2][j] + 1);
                } else {
                    dp[i][j] = 1;
                }
            }

            ans += dp[i][j];
        }
    }

    cout << ans << '\n';

    return 0;
}
