#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

using namespace std;
using namespace __gnu_pbds;

template <typename K, typename V, typename Comp = std::less<K>>
using order_statistic_map = __gnu_pbds::tree<
	K, V, Comp,
	__gnu_pbds::rb_tree_tag,
	__gnu_pbds::tree_order_statistics_node_update
>;

template <typename K, typename Comp = std::less<K>>
using order_statistic_set = order_statistic_map<K, __gnu_pbds::null_type, Comp>;

struct Elem {
    int val;
    int id;

    Elem(int val_, int id_) : val(val_), id(id_) {}

    bool operator<(const Elem& other) const {
        return val < other.val;
    }
};

struct Solver {
    Solver() {
        int n;
        cin >> n;

        vector<Elem> a(n);
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            a[i] = Elem(val, i);
        }

        int64_t ans = 0;

        order_statistic_set<Elem> s;

        for (int i = 0; i < n; i++) {
            cout << i << " " << a[i].val << " " << s.order_of_key(a[i]) << '\n';
        }
    }
};

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) Solver();
    return 0;
}
