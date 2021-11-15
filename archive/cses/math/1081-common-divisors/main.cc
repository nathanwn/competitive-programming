#include <bits/stdc++.h>

using namespace std;

constexpr int N = (int) 1e6;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> cnt(N + 1, 0);

    for (int i = 0; i < n; i++) {
        cin >> x[i];
        cnt[x[i]]++;
    }

    int ans = -1;

    for (int a = N; a > 0; a--) {
        int cnt_multiples = 0; // number of multiples of a in x

        // m = ka (k >= 1)
        for (int m = a; m <= N; m += a) {
            cnt_multiples += cnt[m];
        }

        if (cnt_multiples > 1) {
            ans = a;
            break;
        }
    }

    assert(ans != -1);
    cout << ans << '\n';

    return 0;
}
