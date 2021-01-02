#include <bits/stdc++.h>

using namespace std;

template <typename T> void minimize(T& a, T b) { a = min(a, b); }
template <typename T> void maximize(T& a, T b) { a = max(a, b); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> h(n + 1, vector<int>(3));

    for (int i = 1; i <= n; i++) {
        cin >> h[i][0] >> h[i][1] >> h[i][2];
    }

    // dp[i][j]: maximum happiness after doing activity j on day i

    vector<vector<int>> dp(n + 1, vector<int>(3, 0));

    dp[0][0] = dp[0][1] = dp[0][2] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (j == k) continue;
                maximize(dp[i][j], dp[i - 1][k] + h[i][j]);
            }
        }
    }

    int ans = 0;
    maximize(ans, dp[n][0]);
    maximize(ans, dp[n][1]);
    maximize(ans, dp[n][2]);

    cout << ans << '\n';

    return 0;
}
