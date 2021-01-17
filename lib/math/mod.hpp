#pragma once

#include <bits/stdc++.h>

using namespace std;

// **Really important note**: inputs of the modAdd, modSub, and modMul
// functions must all be normalized (within the range [0..mod - 1]) before use

/// @status:
///   - modMul and modPow tested on:
///      https://cses.fi/problemset/task/1095
///      https://cses.fi/problemset/task/1712
///   - modAdd, modSub, modMul, extGcd, modInv tested on:
///      https://cses.fi/problemset/task/1082
///   - C (binary coefficient) tested on:
///      https://cses.fi/problemset/task/1079

const int N = (int) 1e6;
const int mod = (int) 1e9 + 7;

int modAdd(int a, int b) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

int modSub(int a, int b) {
    a -= b;
    if (a < 0) a += mod;
    return a;
}

int modMul(int a, int b) {
    int64_t res = (int64_t) a * b;
    return (int) (res % mod);
}

int64_t binPow(int64_t a, int64_t x) {
    int64_t res = 1;
    while (x) {
        if (x & 1) res *= a;
        a *= a;
        x >>= 1;
    }
    return res;
}

int64_t modPow(int64_t a, int64_t x) {
    int res = 1;
    while (x) {
        if (x & 1) res = modMul(res, a);
        a = modMul(a, a);
        x >>= 1;
    }
    return res;
}

/// This solves the equation ax + by = gcd(a, b);
/// Input: a, b
//  Output: g (returned), x, y (passed by ref)
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

/// This mod inverse function applies Fermat's little theorem
//  Can only be used if m is prime, and a and m are coprime
int64_t modInvPrimeMod(int64_t a, int64_t m) {
    return modPow(a, m - 2);
}

int64_t modInv(int64_t a) {
    int64_t x, y;
    int64_t g = extGcd(a, mod, x, y);
    assert(g == 1);
    return (x % mod + mod) % mod;
}

int inv[N + 1];

int calcInv() {
    inv[1] = 1;

    for(int i = 2; i <= N; ++i) {
        inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    }
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

