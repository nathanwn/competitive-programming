#include <bits/stdc++.h>

using namespace std;

struct SegmentTree {
    using T = int64_t;

    struct Node {
        int from;
        int to;
        T val;
        T lazy;
        bool is_lazy;
    };

    const T dlazy = 0;
    const T dquery = 0;

    int n;
    vector<Node> t;

    SegmentTree(vector<int>& a) : n(a.size()), t(n * 4) {
        build(a, 0, 0, n - 1);
    }

    inline int left(int u)  { return 2 * u + 1; }
    inline int right(int u) { return 2 * u + 2; }

    T merge(T x, T y) {
        return x + y;
    }

    void build(vector<int>& a, int u, int from, int to) {
        if (from == to) {
            t[u] = Node({from, to, a[from], dlazy, false});
            return;
        }

        int mid = (from + to) / 2;
        build(a, left(u), from, mid);
        build(a, right(u), mid + 1, to);
        T val = merge(t[left(u)].val, t[right(u)].val);
        t[u] = Node({from, to, val, dlazy, false});
    }

    void pushDown(int u) {
        t[left(u)].val += t[u].lazy;
        t[right(u)].val += t[u].lazy;
        t[left(u)].lazy += t[u].lazy;
        t[right(u)].lazy += t[u].lazy;
        t[u].lazy = dlazy;
    }

    T query(int from, int to, int u=0) {
        if (from <= t[u].from && t[u].to <= to) return t[u].val;
        if (to < t[u].from || t[u].to < from) return dquery;
        pushDown(u);
        return merge(query(from, to, left(u)), query(from, to, right(u)));
    }

    void apply(int u, T delta) {
        t[u].val += delta;
        t[u].lazy += delta;
    }

    void update(int from, int to, T delta, int u=0) {
        if (from > to) return;

        if (from == t[u].from && to == t[u].to) {
            apply(u, delta);
            return;
        }

        pushDown(u);

        int mid = (t[u].from + t[u].to) / 2;
        update(from, min(to, mid), delta, left(u));
        update(max(from, mid + 1), to, delta, right(u));
        t[u].val = merge(t[left(u)].val, t[right(u)].val);
    }

};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> x(n);

    for (int i = 0; i < n; i++) cin >> x[i];
    SegmentTree st(x);

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;

        if (t == 1) {
            int a, b, u;
            cin >> a >> b >> u;
            a--; b--;
            st.update(a, b, u);
        } else {
            int k;
            cin >> k;
            k--;
            cout << st.query(k, k) << '\n';
        }
    }

    return 0;
}
