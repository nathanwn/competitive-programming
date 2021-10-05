#include <bits/stdc++.h>

using namespace std;

const int N = (int) 1e6;
const int mod = (int) 1e9 + 7;

int modMul(int a, int b) {
    int64_t res = (int64_t) a * b;
    return (int) (res % mod);
}

int64_t extGcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int64_t x1, y1;
    int64_t g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    assert(g == 1);
    return g;
}

int64_t modInv(int64_t a) {
    int64_t x, y;
    int64_t g = extGcd(a, mod, x, y);
    assert(g == 1);
    return (x % mod + mod) % mod;
}

int fact[N + 1];
int inv_fact[N + 1];

void calcFact() {
    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = modMul(fact[i - 1], i);
    }
    inv_fact[N] = modInv(fact[N]);
    for (int i = N - 1; i >= 0; i--) {
        inv_fact[i] = modMul(inv_fact[i + 1], i + 1);
    }
}

int C(int n, int k) {
    return modMul(fact[n], modMul(inv_fact[k], inv_fact[n - k]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    calcFact();

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        cout << C(a, b) << '\n';
    }

    return 0;
}
