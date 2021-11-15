#include <bits/stdc++.h>

using namespace std;

int64_t modAdd(int64_t a, int64_t b, int64_t mod) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

int64_t modSub(int64_t a, int64_t b, int64_t mod) {
    a -= b;
    if (a < 0) a += mod;
    return a;
}

int64_t modMul(int64_t a, int64_t b, int64_t mod) {
    int64_t res = a * b;
    return res % mod;
}

/// This solves the equation ax + by = gcd(a, b);
/// Input: a, b
/// Output: g (returned), x, y (passed by ref)
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

int64_t modInv(int64_t a, int64_t mod) {
    int64_t x, y;
    int64_t g = extGcd(a, mod, x, y);
    assert(g == 1);
    return (x % mod + mod) % mod;
}

const int64_t mod = (int64_t) 1e9 + 7;

/// Idea: Each divisor i appears floor(n / i) times in the sum
/// => sum = sum_{d = 1 to n} floor(n / i) * i
/// How to calculate this sum in less than worst-case O(n)?
///   Let q = floor(n / i).
///   There are multiple values of i that produce the same value of q
/// Interesting property:
///   Given q. Let l and r be the smallest and largest integer such that
///   floor(n / l) = floor(n / r) = q.
///   Then r = floor(n / q)
/// With this property, if we know l and q, then we can calculate r.
/// Then with each value of q, we add q * sum([l, r]) to ans
/// According to some sources, the number of distinct q values is roughly
/// sqrt(n), but this will need a proof.
///
/// sum([l, r]) = sum{1 to r} - sum{1 to (l - 1)}
/// We all know: sum{1 to n} = n * (n + 1) / 2
/// We should also know that: sum{1 to n} = n * floor((n + 1) / 2)
///
/// **Really important note**: inputs of the modAdd, modSub, and modMul
/// functions must all be normalized (within the range [0..mod - 1]).
/// Also, should mod both numbers a and b before a * b to avoid overflow

int64_t sumDivisor(int64_t n) {
    int64_t ans = 0;
    int64_t l = 1;

    while (l <= n) {
        int64_t q = n / l;
        int64_t r = n / q;
        int64_t rsum = (r % 2 == 0) ? modMul((r / 2) % mod, (r + 1) % mod, mod) :
                                      modMul(r % mod, (r + 1) / 2 % mod, mod);
        int64_t lsum = (l % 2 == 0) ? modMul((l - 1) % mod, (l / 2) % mod, mod) :
                                      modMul((l - 1) / 2 % mod, l % mod, mod);

        // This is another way to calculate rsum and lsum
        // Submitted and got AC, but is much slower
        // int64_t rsum = modMul(r % mod, (r + 1) % mod, mod);
        // rsum = modMul(rsum, modInv(2, mod), mod);
        // int64_t lsum = modMul((l - 1) % mod, l % mod, mod);
        // lsum = modMul(lsum, modInv(2, mod), mod);

        int64_t l_to_r = modSub(rsum, lsum, mod);
        int64_t incr = modMul(q % mod, l_to_r, mod);
        ans = modAdd(ans, incr, mod);
        l = r + 1;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n;
    cin >> n;
    cout << sumDivisor(n) << '\n';

    return 0;
}
