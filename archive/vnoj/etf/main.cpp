#include <bits/stdc++.h>

using namespace std;

int etf(int n) {
    int phi = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {  // i is a prime factor of n
            while (n % i == 0) n /= i;
            phi -= phi / i;
        }
    }
    if (n > 1) {  // n is now the sole prime factor >=sqrt of original number
        phi -= phi / n;
    }
    return phi;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int x;
        cin >> x;
        cout << etf(x) << '\n';
    }
    return 0;
}
