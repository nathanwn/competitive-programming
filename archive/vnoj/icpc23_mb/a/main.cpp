#include <bits/stdc++.h>

using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    if (a < b) swap(a, b);

    while (b != 0) {
        int64_t c = a % b;
        a = b;
        b = c;
    }

    return a;
}

struct Solver {
    vector<int64_t> fibs;

    Solver() {
        int64_t x = 1;
        int64_t y = 1;
        while (x + y <= (int64_t)1e18) {
            int64_t z = x + y;
            fibs.push_back(z);
            x = y;
            y = z;
        }
    }

    int64_t solve(int64_t x, int offset) {
        if (x == 1) return 1;

        int64_t ans = 0;

        for (int i = offset; i < (int)fibs.size(); i++) {
            if (x % fibs[i] == 0) {
                ans += solve(x / fibs[i], i);
            }
        }

        return ans;
    }
};

int main() {
    Solver solver;

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int64_t n;
        cin >> n;
        cout << solver.solve(n, 0) << "\n";
    }

    return 0;
}
