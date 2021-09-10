#include <assert.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Let xs be the set of type-1 players - wanting to have 0 loss.
 * Let ys be the set of type-2 players - wanting to have at least 1 win.
 * Let xs[p] be any player in xs.
 * Let ys[q] be any player in ys.
 * Let 'a > b' denote the fact that a wins against b.
 * Let 'a < b' denote the fact that a loses against b.
 * Let 'a = b' denote the fact that a draws against b.
 * Let 'a >= b' denote the fact that a DOES NOT lose against b.
 * Let 'a <= b' denote the fact that a DOES NOT win against b.
 *
 * Observations:
 * 1) xs[p1] == xs[p2] for any pair of p1 != p2
 * 2) xs[p] >= ys[q] for any pair of p, q. Also, it doesn't matter if
 *    each game of this type result in `>` or `=`, since either way:
 *    no player from xs get a loss, and
 *    no player from ys get a win
 * 3) Since each player in ys must get a win and they cannot win against
 *    xs players, they must get wins from each other. The question now is
 *    how to distribute the wins evenly, so that everyone can get 1 win.
 *    This is pretty simple - just make a cycle:
 *      ys[0] > ys[1],
 *      ys[1] > ys[2],
 *      ys[2] > ys[3],
 *      ...,
 *      ys[m] > ys[0], where m = |ys|
 *    There is no solution if |ys| == 1 or |ys| == 2.
**/

struct Solution {
    int n;
    string s;

    Solution() {
        cin >> n >> s;

        vector<int> xs; // type-1 players
        vector<int> ys; // type-2 players

        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                xs.push_back(i);
            } else {
                ys.push_back(i);
            }
        }

        if ((int) ys.size() == 1 || (int) ys.size() == 2) {
            cout << "NO\n"; return;
        } else {
            cout << "YES\n";
        }

        // All games are draws by default
        vector<vector<char> > a(n, vector<char>(n, '='));

        for (int i = 0; i < n; i++) {
            a[i][i] = 'X';
        }

        for (int p = 0; p < (int) xs.size(); p++) {
            for (int q = 0; q < (int) ys.size(); q++) {
                a[xs[p]][ys[q]] = '=';
                a[ys[q]][xs[p]] = '=';
            }
        }

        for (int q = 0; q < (int) ys.size(); q++) {
            int r = (q + 1 == (int) ys.size()) ? 0 : q + 1;
            a[ys[q]][ys[r]] = '+';
            a[ys[r]][ys[q]] = '-';
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j];
            }
            cout << '\n';
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    for (int i = 1; i <= t; i++) {
        Solution();
    }

    return 0;
}
