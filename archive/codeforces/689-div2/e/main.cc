#include <bits/stdc++.h>

using namespace std;

struct Solver {
    Solver() {
        int64_t water, min_amount, max_amount, days, loss, gain;
        cin >> water >> min_amount >> max_amount >> days >> loss >> gain;

        if (gain < loss) {
            // Strategy: Try to add as long as we can
            int64_t delta = loss - gain;

            int64_t days_before_fail = 0;

            // Check if we can add initially
            if (water + gain > max_amount) {
                water -= loss;
                days_before_fail++;
            }

            days_before_fail += (water - min_amount) / delta;
            cout << (days <= days_before_fail ? "Yes" : "No") << '\n';
        } else { // gain >= loss
            // Strategy: Try not to add unless absolutely have to
            set<int64_t> s;

            while (days > 0 && s.find(water) == s.end()) {
                s.insert(water);
                if (water - loss < min_amount) {
                    if (water + gain > max_amount) {
                        cout << "No" << '\n';
                        return;
                    }
                    water += gain;
                }

                int64_t days_before_add_again = (water - min_amount) / loss;
                water -= loss * days_before_add_again;
                days -= days_before_add_again;
            }

            cout << "Yes" << '\n';
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Solver solver;

    return 0;
}
