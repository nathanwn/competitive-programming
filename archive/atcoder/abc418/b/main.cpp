#include <algorithm>
#include <bitset>
#include <iostream>
#include <iomanip>
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
    double f(string& s, int st, int en) {
        if (s[st] != 't' || s[en] != 't') return 0;
        int t = 0;
        for (int i = st; i <= en; i++) {
            if (s[i] == 't') t++;
        }
        int n = t - 2;
        int d = en - st + 1 - 2;
        return (double) n / d;
    }

    Solver(istream& in, ostream& out) {
        string s;
        in >> s;
        int n = s.size();
        double ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i - 2; j++) {
                ans = max(ans, f(s, j, i));
            }
        }
        out << ans << "\n";
    }
};

int main() {
    cout << fixed << setprecision(10);
    Solver solver(cin, cout);
    return 0;
}
