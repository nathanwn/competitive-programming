#include <iostream>
#include <vector>
#include <map>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

struct Solver {
    Solver(istream& in, ostream& out) {
        int n, m;
        in >> n >> m;
        map<int, int> cnt;
        for (int i = 0; i < n; i++) {
            int x;
            in >> x;
            if (cnt.count(x)) {
                cnt[x]++;
            } else {
                cnt[x] = 1;
            }
        }
        for (int j = 0; j < m; j++) {
            int x;
            in >> x;
            if (cnt.count(x)) {
                cnt[x]--;
            }
        }
        for (auto [k, v] : cnt) {
            for (int i = 0; i < v; i++) {
                out << k << ' ';
            }
        }
        out << '\n';
    }
};

int main() {
    Solver solver(cin, cout);
    return 0;
}
