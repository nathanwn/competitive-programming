#pragma once

#include <bits/stdc++.h>

using namespace std;

/// Sieve of Eratosthenes
/// @status: kind of tested
/// @benchmark:
///   N = 1e7: 0.15s
///   N = 1e8: 1.60s

const int N = (int) 1e8;
bool is_prime[N + 1];
vector<int> primes;

void primeSieve() {
    fill(is_prime, is_prime + N + 1, 1);

    is_prime[0] = is_prime[1] = 0;

    for (int i = 4; i <= N; i += 2) is_prime[i] = 0;

    for (int i = 3; i * i <= N; i += 2) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= N; j += i * 2) {
            is_prime[j] = 0;
        }
    }

    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
}
