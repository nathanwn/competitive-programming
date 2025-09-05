#include <bits/stdc++.h>

using namespace std;

struct Solver {
    Solver() {
        int n, b;
        cin >> n >> b;

        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        sort(a.begin(), a.end());

        for (int i = 1; i < n; i++) {
            a[i] += a[i - 1];
        }

        int ans = 0;
        int left = 0;
        int right = n - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (a[mid] <= b) {
                ans = mid + 1;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        cout << ans << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        cout << "Case #" << ti << ": ";
        Solver solver;
    }

    return 0;
}
