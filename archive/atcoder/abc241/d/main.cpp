#include <bits/stdc++.h>

#ifdef LOCAL
// #include "debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

int main() {
    int q;
    cin >> q;
    typedef multiset<int64_t> MSet;
    typedef MSet::iterator MSetIt;
    MSet s;

    while (q--) {
        int t;
        int64_t x;
        cin >> t >> x;

        if (t == 1) {
            s.insert(x);
        } else {
            int k;
            cin >> k;

            if (t == 2) {
                // find kth largest among values <= x
                MSetIt first_gt_x = s.upper_bound(x);
                MSetIt it = first_gt_x;
                for (int i = 0; i < k; i++) {
                    if (it == s.begin()) {
                        it = s.end();
                        break;
                    } else {
                        it--;
                    }
                }
                int64_t ans = (it == s.end()) ? -1 : *it;
                cout << ans << '\n';
            } else {
                // find kth smallest among values >= x
                MSetIt first_gte_x = s.lower_bound(x);
                MSetIt it = first_gte_x;
                if (it != s.end()) {
                    for (int i = 0; i < k - 1; i++) {
                        // --s.end == iter of last element
                        if (it == --s.end()) {
                            it = s.end();
                            break;
                        } else {
                            it++;
                        }
                    }
                }
                int64_t ans = (it == s.end()) ? -1 : *it;
                cout << ans << '\n';
            }
        }
    }

    return 0;
}
