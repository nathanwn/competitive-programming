#include <bits/stdc++.h>

using namespace std;

int add(int a, int b, int mod) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

int mult(int a, int b, int mod) {
    int64_t res = (int64_t) a * b;
    return (int) (res % mod);
}

int f(int g, int a, int b, int l) {
    return add(mult(g, a, l + 1), b, l + 1);
}

/**
 * Idea: put all w and g values into a list, sort them, then go from left
 * to right while keep track of the longest range and answer when a
 * w value is encountered
**/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n, l, a, b, g;
    cin >> k >> n >> l >> a >> b >> g;

    vector<int> w(k);

    vector<pair<int, bool>> vp; // second == true if first is a w value
    vp.emplace_back(0, false);

    for (int j = 0; j < k; j++) {
        cin >> w[j];
        vp.emplace_back(w[j], true);
    }

    for (int i = 1; i <= n; i++) {
        vp.emplace_back(g, false);
        g = f(g, a, b, l);
    }

    sort(vp.begin(), vp.end());

    int longest = 0;
    int lastG = 0;

    for (int i = 1; i < (int) vp.size(); i++) {
        if (vp[i].second) {
            int ans = vp[i].first - lastG - 1;
            ans = max(ans, longest);
            cout << ans << '\n';
        } else {
            longest = max(longest, vp[i].first - lastG - 1);
            lastG = vp[i].first;
        }
    }

    return 0;
}
