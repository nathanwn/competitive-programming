#include <bits/stdc++.h>

using namespace std;

struct Query {
    int r;
    double p;
};

struct Solver {
    Solver() {
        int n, m;
        cin >> n >> m;

        vector<int> a(n + 1);

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        vector<Query> q;

        for (int j = 0; j < m; j++) {
            int r;
            double p;
            cin >> r >> p;
            q.push_back({r, p});
        }

        int k = n; // a[k]: first element from the right that is not in the
                   // correct position initially

        while (k > 0 && a[k] == k) k--;

        if (k == 0) {
            cout << "1.0\n";
            return;
        }

        double ans = 0;

        for (int i = 0; i < m; i++) {
            if (q[i].r >= k) {
                ans += (1.0 - ans) * q[i].p;
            }
        }

        cout << fixed
            << setprecision(numeric_limits<double>::digits10)
            << ans << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        Solver solver;
    }

    return 0;
}
