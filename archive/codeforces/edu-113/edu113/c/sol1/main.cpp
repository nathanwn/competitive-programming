/**
 * - If there are more than 1 elements having the largest value in a,
 *   then any permutation would work. Then ans = n!
 * - Let m be the largest value in a
 * - If there is only 1 element having the largest value m in a:
 *   - No permutation satisfies if there is no (m - 1) in a
 *   - Let k be the number of times (m - 1) appears in a.
 *   - The value m cannot come after all (m - 1) values in a
 *   valid permutation.
 *   - To create any permutation, we can follow these steps:
 *     . Step 1: Arrange m and (m - 1) values in some order.
 *     . Step 2: Choose k + 1 positions for these values
 *     . Step 3: Arrange the remaining n - k - 1 remaining values in some order.
 *     . We do not need to choose positions for these remaining values.
 *   - To create an invalid permutation in this case
 *     . Step 1: Put m at the very end and arrange the (m - 1) values.
 *              There are k! ways to do this.
 *     . Step 2: Choose k + 1 positions for these values.
 *              There are nC(k + 1) ways to do this.
 *     . Step 3: Arrange the remaining n - k - 1 remaining values in some order.
 *              There are (n - k + 1)! ways to do this.
 *   - Answer would be:
 *       n! - k! * nC(k + 1) * (n - k - 1)!
 *     = n! - k! * n!/((k + 1)!(n - k - 1)!) * (n - k - 1)!
 *     = n! - n!/(k + 1)
**/

#include <iostream>
#include <vector>

using namespace std;

const int mod = 998244353;

int modAdd(int a, int b) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

int modSub(int a, int b) {
    a -= b;
    if (a < 0) a += mod;
    return a;
}

int modMul(int a, int b) {
    int64_t res = (int64_t) a * b;
    return (int) (res % mod);
}

struct Solution {
    int n;
    vector<int> a;

    Solution() {
        cin >> n;
        a.resize(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        cout << solve() << '\n';
    }

    int solve() {
        int m = INT_MIN;

        for (int i = 0; i < n; i++) {
            m = max(m, a[i]);
        }

        int m_cnt = 0;

        for (int i = 0; i < n; i++) {
            m_cnt += (a[i] == m);
        }

        if (m_cnt > 1) {
            int ans = 1;
            for (int i = 2; i <= n; i++) {
                ans = modMul(ans, i);
            }
            return ans;
        }

        int k = 0;

        for (int i = 0; i < n; i++) {
            k += (a[i] == m - 1);
        }

        if (k == 0) return 0;

        int y = 1;

        for (int i = 2; i <= n; i++) {
            if (i != k + 1) y = modMul(y, i);
        }

        int x = modMul(y, k + 1);
        return modSub(x, y);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    for (int i = 0; i < t; i++) {
        Solution();
    }

    return 0;
}
