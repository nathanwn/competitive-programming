/**
 * Problem: Compromise - Source: UVa
 **/

#include <bits/stdc++.h>

using namespace std;

template <typename T>
vector<T> GetLCS(vector<T>& x, vector<T>& y) {
    int m = x.size();
    int n = y.size();
    vector<vector<int>> lcs(m + 1, vector<int>(n + 1, 0));
    vector<vector<pair<int, int>>> trace(m + 1, vector<pair<int, int>>(n + 1));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                trace[i][j] = {-1, -1};
            } else {
                if (lcs[i - 1][j] > lcs[i][j - 1]) {
                    lcs[i][j] = lcs[i - 1][j];
                    trace[i][j] = {-1, 0};
                } else {
                    lcs[i][j] = lcs[i][j - 1];
                    trace[i][j] = {0, -1};
                }
            }
        }
    }

    vector<T> res;
    int cur_i = m;
    int cur_j = n;

    while (cur_i != 0 && cur_j != 0) {
        if (trace[cur_i][cur_j] == make_pair(-1, -1)) {
            res.push_back(x[cur_i - 1]);
        }
        int next_i = cur_i + trace[cur_i][cur_j].first;
        int next_j = cur_j + trace[cur_i][cur_j].second;
        cur_i = next_i;
        cur_j = next_j;
    }

    reverse(res.begin(), res.end());

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> x;
    vector<string> y;
    string s;

    while (cin >> s) {
        x.clear();
        y.clear();

        while (s != "#") {
            x.push_back(s);
            cin >> s;
        }

        cin >> s;

        while (s != "#") {
            y.push_back(s);
            cin >> s;
        }

        vector<string> ans = GetLCS(x, y);

        for (int i = 0; i < (int)ans.size(); i++) {
            cout << ans[i] << (i != (int)ans.size() - 1 ? " " : "");
        }
        cout << '\n';
    }

    return 0;
}
