#pragma once

#include <bits/stdc++.h>

using namespace std;

/// This is actually the Sieve of Eratosthenes algorithm
/// @status: tested with:
///   https://cses.fi/problemset/task/1713
/// @benchmark:
///   N = 1e7: 0.25s
///   N = 1e8: 2.81s

const int N = (int) 1e8;
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

