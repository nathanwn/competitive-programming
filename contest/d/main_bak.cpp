#include <bits/stdc++.h>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using i64 = int64_t;
const i64 VERSTAPPEN = i64(1e6);

i64 find_min_a(i64 n) {
    i64 left = 0;
    i64 right = VERSTAPPEN;
    i64 min_a = -1;
    while (left <= right) {
        i64 mid = left + (right - left) / 2;
        i64 cube = mid * mid * mid;
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

pair<i64, i64> solve(i64 n, i64 min_a) {
    for (i64 a = min_a; a <= VERSTAPPEN; a++) {
        i64 a_cube = a * a * a;
        i64 target = a_cube - n;
        i64 left = 1;
        i64 right = VERSTAPPEN;
        while (left <= right) {
            i64 mid = left + (right - left) / 2;
            i64 b_cube = mid * mid * mid;
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
    i64 min_a = find_min_a(n);
    pair<i64, i64> ans = solve(n, min_a);
    if (ans.first == -1) {
        cout << "-1\n";
    } else {
        cout << ans.first << " " << ans.second << "\n";
    }
    return 0;
}
