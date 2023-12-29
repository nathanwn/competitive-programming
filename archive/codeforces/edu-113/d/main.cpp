#include <bits/stdc++.h>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...) 42
#endif

using namespace std;

struct Point {
    int x, y;
    Point(int x_, int y_) : x(x_), y(y_) {}
};

#ifdef LOCAL
string to_string(const Point& p) {
    return to_string(make_pair(p.x, p.y));
}
#endif

bool cmp_by_x(const Point& p, const Point& q) {
    return p.x < q.x;
}

bool cmp_by_y(const Point& p, const Point& q) {
    return p.y < q.y;
}


struct Solution {
    Solution() {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> xs(n);
        vector<int> ys(m);
        vector<Point> p;

        for (int i = 0; i < n; i++) cin >> xs[i];
        for (int j = 0; j < m; j++) cin >> ys[j];

        for (int z = 0; z < k; z++) {
            int x, y;
            cin >> x >> y;
            p.emplace_back(x, y);
        }

        unordered_set<int> x_ids;
        for (int i = 0; i < n; i++) {
            x_ids.insert(xs[i]);
        }

        unordered_set<int> y_ids;
        for (int i = 0; i < m; i++) {
            y_ids.insert(ys[i]);
        }

        vector<Point> x_group;
        vector<Point> y_group;

        for (int z = 0; z < k; z++) {
            if (x_ids.find(p[z].x) == x_ids.end()) {
                y_group.push_back(p[z]);
            }
            else if (y_ids.find(p[z].y) == y_ids.end()) {
                x_group.push_back(p[z]);
            }
        }

        sort(x_group.begin(), x_group.end(), cmp_by_y);
        sort(y_group.begin(), y_group.end(), cmp_by_x);

        int64_t ans = 0;

        for (int i = 0; i < n - 1; i++) {
            int x_low = xs[i];
            int x_high = xs[i + 1];
            int low = upper_bound(
                y_group.begin(), y_group.end(), Point(x_low, -1), cmp_by_x
            ) - y_group.begin();
            int high = upper_bound(
                y_group.begin(), y_group.end(), Point(x_high, -1), cmp_by_x
            ) - y_group.begin();
            // We also need to eliminate pairs with the same y
            int num = high - low;
            ans += 1LL * num * (num - 1) / 2;
            unordered_map<int, int> same_y;
            for (int j = low; j < high; j++) {
                int y = y_group[j].y;
                if (same_y.find(y) == same_y.end()) {
                    same_y[y] = 0;
                }
                same_y[y]++;
            }
            for (const auto& y_cnt : same_y) {
                int cnt = y_cnt.second;
                ans -= 1LL * cnt * (cnt - 1) / 2;
            }
        }

        for (int i = 0; i < m - 1; i++) {
            int y_low = ys[i];
            int y_high = ys[i + 1];
            int low = upper_bound(
                x_group.begin(), x_group.end(), Point(-1, y_low), cmp_by_y
            ) - x_group.begin();
            int high = upper_bound(
                x_group.begin(), x_group.end(), Point(-1, y_high), cmp_by_y
            ) - x_group.begin();
            int num = high - low;
            ans += 1LL * num * (num - 1) / 2;
            unordered_map<int, int> same_x;
            for (int j = low; j < high; j++) {
                int x = x_group[j].x;
                if (same_x.find(x) == same_x.end()) {
                    same_x[x] = 0;
                }
                same_x[x]++;
            }
            for (const auto& x_cnt : same_x) {
                int cnt = x_cnt.second;
                ans -= 1LL * cnt * (cnt - 1) / 2;
            }
        }

        cout << ans << "\n";
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
