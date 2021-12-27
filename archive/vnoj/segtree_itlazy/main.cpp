#include <iostream>
#include <vector>
#include <limits>
#include <stdint.h>
#include <iomanip>

using namespace std;

template <typename T>
struct SegmentTree {
    T VAL_EMPTY;
    T LAZY_EMPTY;
    int n;
    vector<T> val;
    vector<T> lazy;
    vector<bool> is_lazy;

    int lc(int i) { return i << 1; }
    int rc(int i) { return (i << 1) + 1; }

    // apply the update to one nodes (usually assignment or increment)
    void apply(T& v, T d) {
        v += d;
    }

    // merge the values of two nodes
    T merge(T x, T y) {
        return max(x, y);
    }

    SegmentTree(vector<int>& a) {
        VAL_EMPTY = numeric_limits<T>::min();
        LAZY_EMPTY = 0;

        n = 1;
        while (n < (int) a.size()) n <<= 1;

        val.resize(n << 1, VAL_EMPTY);
        lazy.resize(n << 1, LAZY_EMPTY);
        is_lazy.resize(n << 1, false);

        for (int i = 0; i < (int) a.size(); i++) {
            val[n + i] = a[i];
        }

        for (int i = n - 1; i > 0; i--) {
            val[i] = merge(val[lc(i)], val[rc(i)]);
        }
    }

    void pushDown(int node) {
        if (is_lazy[node]) {
            apply(val[lc(node)], lazy[node]);
            apply(lazy[lc(node)], lazy[node]);
            apply(val[rc(node)], lazy[node]);
            apply(lazy[rc(node)], lazy[node]);
            lazy[node] = LAZY_EMPTY;
            is_lazy[node] = false;
            is_lazy[lc(node)] = true;
            is_lazy[rc(node)] = true;
        }
    }

    void update(int low, int high, int d, int node, int nlow, int nhigh) {
        if (low <= nlow && nhigh <= high) {
            apply(val[node], d);
            apply(lazy[node], d);
            is_lazy[node] = true;
            return;
        }
        if (high < nlow || nhigh < low) {
            return;
        }
        pushDown(node);
        int nmid = nlow + (nhigh - nlow) / 2;
        update(low, high, d, lc(node), nlow, nmid);
        update(low, high, d, rc(node), nmid + 1, nhigh);
        val[node] = merge(val[lc(node)], val[rc(node)]);
    }

    void update(int low, int high, int d) {
        update(low, high, d, 1, 0, n - 1);
    }

    T query(int low, int high) {
        return query(low, high, 1, 0, n - 1);
    }

    T query(int low, int high, int node, int nlow, int nhigh) {
        if (low <= nlow && nhigh <= high) {
            return val[node];
        }
        if (high < nlow || nhigh < low) {
            return VAL_EMPTY;
        }
        pushDown(node);
        int nmid = nlow + (nhigh - nlow) / 2;
        return merge(
            query(low, high, lc(node), nlow, nmid),
            query(low, high, rc(node), nmid + 1, nhigh)
        );
    }
};

int main() {
    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    SegmentTree<int64_t> st(a);

    int q; cin >> q;

    for (int i = 0; i < q; i++) {
        st.print();
        int qt; cin >> qt;
        if (qt == 1) {
            int low, high, d;
            cin >> low >> high >> d;
            low--; high--;
            st.update(low, high, d);
        } else {
            int low, high;
            cin >> low >> high;
            low--; high--;
            cout << st.query(low, high) << '\n';
        }
    }

    return 0;
}
