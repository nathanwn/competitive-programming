#include <bits/stdc++.h>

using namespace std;

struct Solver {
    const int SQRT = 31623;
    const int64_t INF = 1e18;
    map<string, int> squares;
    map<int, int64_t> memo;
    string s;
    int n;

    int64_t solve(int from) {
        if (from > n) return INF;
        if (memo.find(from) != memo.end()) return memo[from];
        if (s[from] == '0') return INF;

        int64_t res = INF;
        string ss;

        for (int i = from; i < min(from + 10, n); i++) {
            ss += s[i];
            if (squares.find(ss) == squares.end()) continue;
            int64_t cur = squares[ss];

            if (i == n - 1) {
                res = min(res, cur);
            }
            else {
                int64_t remain = solve(i + 1);
                if (remain == INF) continue;
                res = min(res, cur + remain);
            }
        }

        memo[from] = res;
        return res;
    }

    Solver() {
        for (int i = 1; i < SQRT; i++) {
            squares.emplace(to_string(i * i), i * i);
        }
        cin >> s;
        n = s.length();
        int64_t ans = solve(0);
        if (ans > (int) 1e9) cout << "-1\n";
        else cout << ans << '\n';
    }
};

int main() {
    Solver solver;
    return 0;
}
