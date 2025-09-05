#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> a(m);

    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    int ans = 0;

    for (int i = 1; i < m; i++) {
        if (a[i] < a[i - 1]) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}
