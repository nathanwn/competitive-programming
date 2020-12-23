#pragma once

/// @status:
///   - modMul and modPow tested on:
///      https://cses.fi/problemset/task/1095
///      https://cses.fi/problemset/task/1712

int modAdd(int a, int b, int mod) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

int modSub(int a, int b, int mod) {
    a -= b;
    if (a < 0) a += mod;
    return a;
}

int modMul(int a, int b, int mod) {
    int64_t res = (int64_t) a * b;
    return (int) (res % mod);
}

uint64_t binPow(uint64_t a, uint64_t x) {
    uint64_t res = 1;
    while (x) {
        if (x & 1) res *= a;
        a *= a;
        x >>= 1;
    }
    return res;
}

uint64_t modPow(uint64_t a, uint64_t x, uint64_t mod) {
    uint64_t res = 1;
    while (x) {
        if (x & 1) res = modMul(res, a);
        a = modMul(a, a);
        x >>= 1;
    }
    return res;
}
