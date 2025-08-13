#include <array>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

struct Solver {
    Solver(istream& in, ostream& out) {
        int n;
        in >> n;
        string s;
        in >> s;
        // Invariant: After each operation, the number of 0s is either
        // - decreased by 2
        // - unchanged
        // How?
        //   00 -> 1: number of 0s decreased by 2
        //   10 -> 0: number of 0s unchanged
        //   01 -> 0: number of 0s unchanged
        //   11 -> 1: number of 0s unchanged
        // s[l, r] is a beautiful string if the number of 0s is even.
        // dp[i][0]: number of substrings of [0..i) ending at i - 1
        // (s[0..i), s[1..i - 1), s[2..i - 1), ...) containing an even number of 0s
        vector<array<int, 2>> dp(n + 1, array<int, 2>());
        dp[0][0] = 0;
        dp[0][1] = 0;
        for (int i = 1; i <= n; i++) {
            if (s[i - 1] == '0') {
                dp[i][0] = dp[i - 1][1];
                dp[i][1] = dp[i - 1][0] + 1;
            } else {
                dp[i][0] = dp[i - 1][0] + 1;
                dp[i][1] = dp[i - 1][1];
            }
        }
        int64_t ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += dp[i][0];
        }
        out << ans << '\n';
    }
};

int main() {
    Solver solver(cin, cout);
    return 0;
}
