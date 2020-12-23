#include <bits/stdc++.h>

using namespace std;

int modMul(int a, int b, int mod) {
    int64_t res = (int64_t) a * b;
    return (int) (res % mod);
}

uint64_t modPow(uint64_t a, uint64_t x, uint64_t mod) {
    uint64_t res = 1;
    while (x) {
        if (x & 1) res = modMul(res, a, mod);
        a = modMul(a, a, mod);
        x >>= 1;
    }
    return res;
}

/**
 * Idea:
 * - Cannot do B^C on the same mod!
 * - Let B^C = x*(M - 1) + y
 *   => A^(B^C) = A^[x * (M - 1) + y] = A^(x * (M - 1)) * A^y
 *   Also: A^(x*(M - 1)) = (A^(M - 1))^x
 *   Since A and M are coprime (because M is a prime number),
 *   according to Fermat's little theorem: A^(M - 1) = 1 (mod M)
 *   => A^(B^C) = A^y (mod M)
 *
 *   B^C = x*(M - 1) + y
 *   => y = B^C (mod (M - 1))
**/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    const int M = (int) 1e9 + 7;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << modPow(a, modPow(b, c, M - 1), M) << '\n';
    }

    return 0;
}
