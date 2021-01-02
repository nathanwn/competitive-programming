#include <bits/stdc++.h>

using namespace std;

template <typename T> void minimize(T& a, T b) { a = min(a, b); }
template <typename T> void maximize(T& a, T b) { a = max(a, b); }

const int MAXN = 100;
const int MAXV = 1e3;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, cap;
    cin >> n >> cap;

    vector<int> w(n + 1);
    vector<int> v(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
    }

    // dp[i][j]: mimimum weight to get value j after checking i items
    const int64_t inf = 1e18;
    const int V = MAXN * MAXV;
    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(V + 1, inf));
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= V; j++) {
            if (j <= v[i]) {
                dp[i][j] = min(dp[i - 1][j], (int64_t) w[i]);
            } else {
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i]);
            }

            if (dp[i][j] <= cap) {
                maximize(ans, j);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
