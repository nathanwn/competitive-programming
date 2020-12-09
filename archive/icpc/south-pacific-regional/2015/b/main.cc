#include <bits/stdc++.h>

using namespace std;

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

    // Intuition: each character `c` of the pattern represents a segment of
    // length `c - 'a' + 1`. What we need to do is to find a way to rearrange
    // the segments in such a way that:
    // - The total sum obtained is maximum
    // - The segments follow the order in which they are given
    // - All segments are disjoint (they do not overlap one another)
    //
    // dp[i][j]: max value can be obtained by using the prefix [1..i] of the pin
    // and the prefix [1..j] of the pattern
    // len: the length of the j segment
    // if we cannot fit all segments given by pattern[1..j] into pin[1..i]:
    //    dp[i][j] = -1
    //    (how to check: check if we can place the jth segment at the very end.
    //    We cannot if either:
    //    (a) i < len: pin[1..i] cannot even fit jth segment alone
    //    (b) dp[i - len][j - 1] != -1: pin[1..i] cannot fit prior
    //    segments in any way that would allow the jth segment to be placed at
    //    the very end of it)
    // else we can fit all segments given by pattern[1..j] into pin[1..j]
    // in that case, either:
    //   (a) we place the jth segment at the very end of the pin, or
    //   (b) we don't place the jth segment at the very end of the pin
    //
    //   dp[i][j] = max(
    //   (a)  dp[i - len][j - 1] + sum(i - len + 1, i),
    //   (b)  dp[i - 1][j]
    //   )
    //
    // Base cases: dp[i][0] = 0 for all i

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int len = pattern[j] - 'a' + 1;

            if (i < len || dp[i - len][j - 1] == -1) {
                dp[i][j] = -1;
            } else {
                dp[i][j] = max(dp[i - 1][j],
                               dp[i - len][j - 1] + sum(i - len + 1, i));
            }
        }
    }

    assert(dp[n][m] != -1);
    cout << dp[n][m] << '\n';

    return 0;
}
