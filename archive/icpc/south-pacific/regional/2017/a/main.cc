#include <bits/stdc++.h>

using namespace std;

int64_t ceilDiv(int64_t a, int64_t b) {
    return (a + b - 1) / b;
}

int main() {
    int n;
    cin >> n;

    vector<int64_t> h(n + 2, 0);
    for (int i = 1; i <= n; i++) cin >> h[i];

    // hl[i] minimum height of column i if it is on the left of the apex
    // hr[i] minimum height of column i if it is on the right of the apex
    vector<int64_t> hl(n + 2, 0);
    vector<int64_t> hr(n + 2, 0);

    hl[1] = h[1];

    for (int i = 2; i <= n; i++) {
        hl[i] = ceilDiv(hl[i - 1], h[i]) * h[i];
    }

    hr[n] = h[n];

    for (int i = n - 1; i > 0; i--) {
        hr[i] = ceilDiv(hr[i + 1], h[i]) * h[i];
    }

    for (int i = 2; i <= n; i++) {
        hl[i] += hl[i - 1];
    }

    for (int i = n - 1; i > 0; i--) {
        hr[i] += hr[i + 1];
    }

    const int64_t inf = 1e18;
    int64_t ans = inf;

    for (int i = 1; i <= n; i++) {
        int64_t vol = 0;
        vol += hl[i - 1];
        vol += hr[i + 1];
        vol += max(hl[i] - hl[i - 1], hr[i] - hr[i + 1]);
        ans = min(ans, vol);
    }

    cout << ans << '\n';

    return 0;
}
