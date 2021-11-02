#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, h, m;
    cin >> n >> h >> m;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<vector<vector<pair<int, int>>>> dp(2, vector<vector<pair<int, int>>>(n + 1, vector<pair<int, int>>(n + 1)));
    dp[0][0][0] = make_pair(0, 0);
    dp[1][0][0] = make_pair(0, 0);
    for (int i = 1; i <= n; i++) {
        dp[0][i][0] = make_pair(0, 0);
        dp[1][i][0] = make_pair(0, 0);
        dp[0][0][i] = make_pair(0, 0);
        dp[1][0][i] = make_pair(0, 0);
    }
    // dp[last][h][m]
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {

        }
    }
    return 0;
}
