#include <bits/stdc++.h>

using namespace std;

template <typename T>
class vec2d : public vector<vector<T>> {
public:
    vec2d(int n=0, int m=0, T t=T())
        : vector<vector<T>>(n, vector<T>(m, t)) {}
};

const int N = 3000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    char s[N + 2];
    char t[N + 2];
    scanf("%s %s", s + 1, t + 1);

    int n = strlen(s + 1);
    int m = strlen(t + 1);

    vec2d<int> dp(n + 1, m + 1, 0);
    vec2d<pair<int, int>> trace(n + 1, m + 1, {0, 0});

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i] == t[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                trace[i][j] = {-1, -1};
            } else {
                if (dp[i - 1][j] > dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                    trace[i][j] = {-1, 0};
                } else {
                    dp[i][j] = dp[i][j - 1];
                    trace[i][j] = {0, -1};
                }
            }
        }
    }

    string ans;

    {
        int i = n;
        int j = m;

        while (i > 0 && j > 0) {
            if (trace[i][j] == make_pair(-1, -1)) {
                ans += s[i];
            }
            int ni = i + trace[i][j].first;
            int nj = j + trace[i][j].second;
            i = ni;
            j = nj;
        }
    }

    reverse(ans.begin(), ans.end());

    assert((int) ans.length() == dp[n][m]);
    cout << ans << '\n';

    return 0;
}
