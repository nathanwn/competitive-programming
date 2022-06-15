#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int inf = 1e9;

template <typename T>
struct vec2d : vector<vector<T>> {
    vec2d(int d0, int d1, T t = T()) : vector<vector<T>>(d0, vector<T>(d1, t)) {}
};

template <typename T>
struct vec3d : vector<vec2d<T>> {
    vec3d(int d0, int d1, int d2, T t = T()) : vector<vec2d<T>>(d0, vec2d<T>(d1, d2, t)) {}
};

template <typename T>
void mini(T &a, T b) {
    a = min(a, b);
}

struct Solver {
    Solver() {
        int target_oxi, target_nitro;
        cin >> target_oxi >> target_nitro;
        int n;
        cin >> n;
        vector<int> vo(n + 1);
        vector<int> vn(n + 1);
        vector<int> w(n + 1);
        for (int i = 1; i <= n; i++) cin >> vo[i] >> vn[i] >> w[i];

        vec3d<int> dp(n + 1, target_oxi + 1, target_nitro + 1, inf);
        // dp[i][to][tn]: minimum weight for volume of $to$ oxi and
        //                                             $tn$ of nitro
        // recurrence:
        // dp[i][to][tn] = min(
        //   dp[i - 1][to][tn]
        //     if dp[i - 1][to][tn] != +inf
        //   dp[i - 1][to_prev][tn_prev] + w[i]
        //     if dp[i - 1][to_prev][tn_prev] != +inf
        //   +inf
        // )
        //   where
        //     to_prev in range[max(0, to-vo[i]), to-1]
        //     tn_prev in range[max(0, tn-vn[i]), tn-1]
        //
        // base case:
        // dp[0][to][tn] = +inf if to > 0 or tn > 0
        // dp[i][0][0] = 0      for all i

        for (int i = 0; i <= n; i++) dp[i][0][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int to = 1; to <= target_oxi; to++) {
                for (int tn = 1; tn <= target_nitro; tn++) {
                    if (dp[i - 1][to][tn] != inf) {
                        mini(dp[i][to][tn], dp[i - 1][to][tn]);
                    }
                    for (int to_prev = max(0, to - vo[i]); to_prev <= to; to_prev++) {
                        for (int tn_prev = max(0, tn - vn[i]); tn_prev <= tn; tn_prev++) {
                            if (dp[i - 1][to_prev][tn_prev] != inf) {
                                mini(dp[i][to][tn], dp[i - 1][to_prev][tn_prev] + w[i]);
                            }
                        }
                    }
                }
            }
        }

        cout << dp[n][target_oxi][target_nitro] << '\n';
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) Solver();
    return 0;
}
