#include <bits/stdc++.h>

using namespace std;

const int N = (int) 1e6;
int spf[N + 1]; // spf[x]: smallest prime factor of x
// vector<int> primes;

void calcSmallestPrimeFactor() {
    for (int i = 2; i <= N; i += 2) spf[i] = 2;
    for (int i = 3; i <= N; i += 2) spf[i] = i;

    for (int i = 3; i * i <= N; i += 2) {
        if (spf[i] != i) continue;
        for (int j = i * i; j <= N; j += i) {
            if (spf[j] == j) spf[j] = i;
        }
    }

    // for (int i = 2; i <= N; i++) {
    //     if (spf[i] == i) primes.push_back(i);
    // }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    calcSmallestPrimeFactor();

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        vector<pair<int, int>> factors;

        while (x > 1) {
            int p = spf[x];
            pair<int, int> factor = {p, 0};
            while (x > 1 && x % p == 0) {
                x /= p;
                factor.second++;
            }
            factors.push_back(factor);
        }

        int ans = 1;

        for (const auto& factor : factors) {
            ans *= factor.second + 1;
        }

        cout << ans << '\n';
    }

    return 0;
}
