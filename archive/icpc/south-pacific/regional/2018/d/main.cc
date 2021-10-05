#include <bits/stdc++.h>

using namespace std;

/**
 * Idea:
 * - Define a left_operation(i) as an action of putting 1 more block on each
 * pile from i downto 0
 * - Define a right_operation(i) as an action of putting 1 more block on each
 * pile from i to n - 1
 *
 *   Let a[l] and a[r] be two consecutive piles (i.e. r = l + 1)
 *   If a[l] > a[r], then left_operation(l) must have occurred (a[l] - a[r])
 * times
 *   Similarly, if a[l] < a[r], then right-operation(r) must have occured
 * (a[r] - a[l]) times
 *
 *   If we (are able to) cancel out all operations that create difference
 * between two consecutive piles, then we would end up with a configuration of
 * all piles having the same height
 *   This configuration is always valid (which is quite trivial to see - to
 * produce such configuration, a bunch of right_operations(0) or
 * (left_operations[n - 1] would suffice.)
 *
 *   Thus, whether a configuration valid or not depends on whether we can cancel
 * out all the operations that create difference between two consecutive piles
 * without running out of blocks in any pile.
 *
 *   Define cummulative_left_operations[i] to be the number of times the ith
 * element participated in a left_operation
 *   Define cummulative_right_operations[i] to be the number of times the ith
 * element participated in a right_operation
 *
 *   Two arrays cummulative_left_operations and cummulative_right_operations
 * can be calculated in O(n)
**/

bool solve() {
    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> operations(n, 0);

    int cummulative_right_operations = 0;

    for (int i = 1; i < n; i++) {
        if (a[i - 1] < a[i]) {
            cummulative_right_operations += a[i] - a[i - 1];
            operations[i] += cummulative_right_operations;
        }
    }

    int cummulative_left_operations = 0;

    for (int i = n - 2; i > -1; i--) {
        if (a[i + 1] < a[i]) {
            cummulative_left_operations += a[i] - a[i + 1];
            operations[i] += cummulative_left_operations;
        }
    }

    for (int i = 0; i < n; i++) {
        if (a[i] < operations[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << (solve() ? "YES" : "NO") << '\n';

    return 0;
}
