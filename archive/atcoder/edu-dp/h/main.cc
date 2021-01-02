#include <bits/stdc++.h>

using namespace std;

template <typename T> void minimize(T& a, T b) { a = min(a, b); }
template <typename T> void maximize(T& a, T b) { a = max(a, b); }

template <typename T>
class vec2d : public vector<vector<T>> {
public:
    vec2d(int n=0, int m=0, T t=T())
        : vector<vector<T>>(n, vector<T>(m, t)) {}
};

const int mod = 1e9 + 7;

void add(int& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

const int N = 1000 + 9;
char g[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w;
    scanf("%d %d", &h, &w);

    for (int i = 1; i <= h; i++) {
        scanf("%s", g[i] + 1);
    }

    for (int i = 0; i <= h; i++) g[i][0] = '#';
    for (int j = 0; j <= w; j++) g[0][j] = '#';

    vec2d<int> dp(h + 1, w + 1, 0);

    dp[1][1] = 1;

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (g[i - 1][j] != '#') add(dp[i][j], dp[i - 1][j]);
            if (g[i][j - 1] != '#') add(dp[i][j], dp[i][j - 1]);
        }
    }

    cout << dp[h][w] << '\n';

    return 0;
}
