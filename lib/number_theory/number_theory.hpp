#ifndef NUMBER_THEORY_H_
#define NUMBER_THEORY_H_

int eulerPhi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n > 1) {
        res -= res / n;
    }
    return res;
}

// Gonna come back to these later
// int64_t BinExp(int64_t a, int64_t x) {
//     int64_t res = 1;
//
//     while (x > 0) {
//         if (x & 1) {
//             res *= a;
//             res %= MOD;
//         }
//         a *= a;
//         a %= MOD;
//         x >>= 1;
//     }
//
//     return res;
// }
//
// int64_t ModInverse(int64_t b) {
//     int64_t res = BinExp(b, MOD - 2);
//     if (res * b % MOD != 1) return -1;
//     return res;
// }

#endif // NUMBER_THEORY_H_
