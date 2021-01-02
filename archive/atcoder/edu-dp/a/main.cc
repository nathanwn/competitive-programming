#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> h(n);

    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    vector<int> cost(n);
    // cost[i]: min cost to travel to i

    cost[0] = 0;
    cost[1] = abs(h[1] - h[0]);

    for (int i = 2; i < n; i++) {
        cost[i] = min(cost[i - 2] + abs(h[i] - h[i - 2]),
                      cost[i - 1] + abs(h[i] - h[i - 1]));
    }

    cout << cost[n - 1] << '\n';

    return 0;
}
