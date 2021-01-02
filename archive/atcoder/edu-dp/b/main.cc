#include <bits/stdc++.h>

using namespace std;

template <typename T> void minimize(T& a, T b) { a = min(a, b); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> h(n);

    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    const int inf = (int) 1e9;
    vector<int> cost(n, inf);
    // cost[i]: min cost to travel to i

    cost[0] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= k; j++) { // step size
            if (i - j < 0) break;
            minimize(cost[i], cost[i - j] + abs(h[i] - h[i - j]));
        }
    }

    cout << cost[n - 1] << '\n';

    return 0;
}
