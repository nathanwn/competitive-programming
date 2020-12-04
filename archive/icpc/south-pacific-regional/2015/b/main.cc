#include <bits/stdc++.h>

using namespace std;

template <typename T> void maximize(T& a, T b) { a = max(a, b); }

vector<char> readBase1() {
    string s;
    cin >> s;
    int len = s.length();
    vector<char> vc(len + 1);

    for (int i = 0; i < len; i++) {
        vc[i + 1] = s[i];
    }

    return vc;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<char> pin = readBase1();
    vector<char> pattern = readBase1();

    int n = pin.size() - 1;
    int m = pattern.size() - 1;

    if (m == 0) {
        cout << "0\n";
        return 0;
    }

    vector<int> presum(n + 1);
    presum[0] = 0;
    for (int i = 1; i <= n; i++) {
        presum[i] = presum[i - 1] + pin[i] - '0';
    }

    auto sum = [&](int l, int r) {
        assert(l > 0);
        return presum[r] - presum[l - 1];
    };

    // dp[i][j]: max value can be obtained by using the prefix [1..i] of the pin
    // and the prefix [1..j] of the pattern
    //
    // dp[i][j] = -1 if we cannot fit pattern[1..j] into pin[1..i]

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            int len = pattern[j] - 'a' + 1;

            if (j == 1) {
                if (i >= len) {
                    maximize(dp[i][j], sum(i - len + 1, i));
                }
            } else {
                if (i >= len && dp[i - len][j - 1] != -1) {
                    maximize(dp[i][j], dp[i - len][j - 1] + sum(i - len + 1, i));
                }
            }
        }
    }

    assert(dp[n][m] != -1);
    cout << dp[n][m] << '\n';

    return 0;
}
