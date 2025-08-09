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
        int n, q;
        in >> n >> q;
        vector<int> a(n);
        vector<int> b(q);
        for (int i = 0; i < n; i++) in >> a[i];
        for (int j = 0; j < q; j++) in >> b[j];

        sort(a.begin(), a.end());

        vector<int64_t> s(n);
        s[0] = a[0];
        for (int i = 1; i < n; i++) s[i] = s[i - 1] + a[i];

        for (int y : b) {
            int lo = 0;
            int hi = n - 1;
            int pos = -1;
            while (lo <= hi) {
                int mi = lo + (hi - lo) / 2;
                if (a[mi] >= y) {
                    pos = mi;
                    hi = mi - 1;
                } else {
                    lo = mi + 1;
                }
            }
            // dbg(y, pos);
            if (pos == -1) {
                out << "-1\n";
            } else {
                int64_t ans = y + 1LL * (y - 1) * (n - pos - 1);
                if (pos > 0) {
                    ans += s[pos - 1];
                }
                out << ans << "\n";
            }
        }
    }
};

int main() {
    Solver solver(cin, cout);
    return 0;
}
