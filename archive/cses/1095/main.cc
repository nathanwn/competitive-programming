#include <bits/stdc++.h>

using namespace std;

constexpr int mod = (int) 1e9 + 7;

int modMul(int a, int b) {
    int64_t res = (int64_t) a * b;
    return (int) (res % mod);
}

uint64_t modPow(uint64_t a, uint64_t x) {
    uint64_t res = 1;
    while (x) {
        if (x & 1) res = modMul(res, a);
        a = modMul(a, a);
        x >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        cout << modPow(a, b) << '\n';
    }

    return 0;
}
