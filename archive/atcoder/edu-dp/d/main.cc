#include <bits/stdc++.h>

using namespace std;

template <typename T> void minimize(T& a, T b) { a = min(a, b); }
template <typename T> void maximize(T& a, T b) { a = max(a, b); }

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

    // dp[i][j]: maximum value obtained after checking items 0..i with
    // capacity j
    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(cap + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= cap; j++) {
            if (j - w[i] < 0) {
                dp[i][j] = dp[i - 1][j];
            } else {
                // two choices: put item i into the knapsack, or leave it
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
            }
        }
    }

    cout << dp[n][cap] << '\n';

    return 0;
}
