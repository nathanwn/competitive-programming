#include <bits/stdc++.h>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using i64 = int64_t;
using i128 = __int128;
const i64 VERSTAPPEN = 5 * i64(1e7);

i128 find_min_a(i128 n) {
    int left = 0;
    int right = VERSTAPPEN;
    i128 min_a = -1;
    while (left <= right) {
        // dbg(left, right);
        i128 mid = left + (right - left) / 2;
        i128 cube = mid * mid * mid;
        if (cube >= n) {
            min_a = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    assert(min_a != -1);
    return min_a;
}

pair<i64, i64> solve(i128 n, i128 min_a) {
    dbg(i64(min_a));
    for (i128 a = min_a; a <= VERSTAPPEN; a++) {
        i128 a_cube = a * a * a;
        i128 target = a_cube - n;
        i128 left = 1;
        i128 right = a - 1;  // b < a
        while (left <= right) {
            i128 mid = left + (right - left) / 2;
            i128 b_cube = mid * mid * mid;
            if (b_cube == target) {
                return {a, mid};
            } else if (b_cube > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
    return {-1, -1};
}


int main() {
    i64 n; cin >> n;
    i128 min_a = find_min_a(n);
    pair<i64, i64> ans = solve(n, min_a);
    if (ans.first == -1) {
        cout << "-1\n";
    } else {
        cout << ans.first << " " << ans.second << "\n";
    }
    return 0;
}
