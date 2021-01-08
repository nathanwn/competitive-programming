#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> x(n + 1);
    vector<int64_t> presum(n + 1);
    presum[0] = 0;

    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        presum[i] = presum[i - 1] + x[i];
    }


    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << presum[b] - presum[a - 1] << '\n';
    }

    return 0;
}
