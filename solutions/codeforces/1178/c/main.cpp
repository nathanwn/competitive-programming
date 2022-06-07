#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int M = 998244353;

void mul(int64_t& a, int64_t x) {
    a *= x;
    a %= M;
}

int64_t binExp(int64_t a, int64_t x) {
    int64_t res = 1;
    while (x > 0) {
        if (x & 1) {
            mul(res, a);
        }
        mul(a, a);
        x >>= 1;
    }
    return res;
}

int main() {
    int w, h;
    cin >> w >> h;
    cout << binExp(2, w + h) << "\n";
    return 0;
}
