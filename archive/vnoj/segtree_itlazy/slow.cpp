#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;

    vector<int64_t> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int q; cin >> q;

    for (int qi = 0; qi < q; qi++) {
        int qt; cin >> qt;
        if (qt == 1) {
            int low, high, d;
            cin >> low >> high >> d;
            low--; high--;
            for (int i = low; i <= high; i++) {
                a[i] += d;
            }
        } else {
            int low, high;
            cin >> low >> high;
            low--; high--;
            int64_t res = numeric_limits<int64_t>::min();
            for (int i = low; i <= high; i++) {
                res = max(res, a[i]);
            }
            cout << res << '\n';
        }
    }

    return 0;
}
