#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

struct Solver {
    Solver() {
        string s;
        cin >> s;
        string t(s.rbegin(), s.rend());
        int n = s.length();

        vector<vector<int>> lcs_len(n + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    lcs_len[i][j] = lcs_len[i - 1][j - 1] + 1;
                } else {
                    lcs_len[i][j] = max(lcs_len[i - 1][j], lcs_len[i][j - 1]);
                }
            }
        }

        cout << (n - lcs_len[n][n]) << '\n';
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) Solver();
    return 0;
}
