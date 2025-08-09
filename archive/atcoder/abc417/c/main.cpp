#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

struct Solver {
    Solver(istream& in, ostream& out) {
        int n; in >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) in >> a[i];

        map<int, int> m;  // key = i + a[i]
        for (int i = 1; i <= n; i++) {
            int k = i + a[i];
            m[k]++;
        }
        int64_t ans = 0;
        for (int j = 1; j <= n; j++) {
            int k = j - a[j];
            ans += m[k];
        }
        out << ans << "\n";
    }
};

int main() {
    Solver solver(cin, cout);
    return 0;
}
