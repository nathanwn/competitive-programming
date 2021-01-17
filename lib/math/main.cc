#include <bits/stdc++.h>
#include "smallest_prime_factor.hpp"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // primeSieve();
    calcSmallestPrimeFactor();
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}
