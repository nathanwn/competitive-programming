#include <bits/stdc++.h>

using namespace std;

struct Solver {
    Solver() {
        int n, k;
        cin >> n >> k;
        vector<char> c(3);
        c[0] = 'a', c[1] = 'b', c[2] = 'c';

        for (int i = 0; i < n; i++) {
            cout << c[i % 3];
        }
        cout << '\n';
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        Solver solver;
    }

    return 0;
}
