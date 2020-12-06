#include <bits/stdc++.h>

using namespace std;

const int N = (int) 1e7;
int divisorCount[N + 1];

void primeSieve() {
    for (int i = 1; i <= N; i++) {
        divisorCount[i] = 0;
    }

    for (int i = 2; i <= N; i++) {
        if (divisorCount[i] > 0) continue;
        divisorCount[i] = 1;

        for (int j = i * 2; j <= N; j += i) {
            divisorCount[j]++;
        }
    }
}

struct Solver {
    int a, b, k;

    Solver(int _a, int _b, int _k) : a(_a), b(_b), k(_k) {}

    int solve() {
        int ans = 0;

        for (int i = a; i <= b; i++) {
            if (divisorCount[i] == k) {
                ans++;
            }
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    primeSieve();

    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int a, b, k;
        cin >> a >> b >> k;
        Solver solver(a, b, k);
        cout << "Case #" << ti << ": " << solver.solve() << '\n';
    }

    return 0;
}
