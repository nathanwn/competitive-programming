#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct SegmentTree {
    SegmentTree(vector<T>& a) {
    }
};

struct Solution {
    Solution() {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> x(n);
        vector<int> y(m);

        for (int i = 0; i < n; i++) cin >> x[i];
        for (int i = 0; i < m; i++) cin >> y[i];
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

