#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

void solve(vector<vector<string>>& words) {
    int n = words[0].size();
    int m = words[1].size();
    vector<vector<int>> lcs_len(n + 1, vector<int>(m + 1, 0));
    vector<vector<pair<int, int>>> lcs_prev(
        n + 1, vector<pair<int, int>>(m + 1, make_pair(0, 0)));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (words[0][i - 1] == words[1][j - 1]) {
                lcs_len[i][j] = lcs_len[i - 1][j - 1] + 1;
                lcs_prev[i][j] = make_pair(i - 1, j - 1);
            } else if (lcs_len[i - 1][j] > lcs_len[i][j - 1]) {
                lcs_len[i][j] = lcs_len[i - 1][j];
                lcs_prev[i][j] = make_pair(i - 1, j);
            } else {
                lcs_len[i][j] = lcs_len[i][j - 1];
                lcs_prev[i][j] = make_pair(i, j - 1);
            }
        }
    }

    vector<string> res;
    pair<int, int> cur = make_pair(n, m);

    while (cur != make_pair(0, 0)) {
        pair<int, int> prev = lcs_prev[cur.first][cur.second];
        if (cur.first - 1 == prev.first && cur.second - 1 == prev.second) {
            res.push_back(words[0][prev.first]);
        }
        cur = prev;
    }

    reverse(res.begin(), res.end());

    for (int i = 0; i < (int)res.size(); i++) {
        if (i != 0) cout << " ";
        cout << res[i];
    }
    cout << "\n";
}

int main() {
    int c = 0;
    vector<vector<string>> words(2);
    string s;

    while (cin >> s) {
        if (s == "#") {
            c++;
            if (c % 2 == 0) {
                solve(words);
                words[0].clear();
                words[1].clear();
            }
        } else {
            words[c % 2].push_back(s);
        }
    }
    return 0;
}
