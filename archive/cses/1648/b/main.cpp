#include <iostream>
#include <vector>

template <typename T>
struct SegmentTree {
    int n;
    std::vector<T> t;

    SegmentTree(std::vector<T>& a, T def) {
        n = 1;
        while (n < (int)a.size()) n <<= 1;
        t.resize(n << 1, def);
        build(a);
    }

    inline int left(int i) { return i << 1; }

    inline int right(int i) { return (i << 1) + 1; }

    void build(std::vector<T>& a) {
        for (int i = 0; i < (int)a.size(); i++) {
            t[n + i] = a[i];
        }
        for (int i = n - 1; i > 0; i--) {
            t[i] = t[left(i)] + t[right(i)];
        }
    }

    T query(int from, int to, int node, int node_from, int node_to) {
        if (from <= node_from && node_to <= to) {
            return t[node];
        }
        if (to < node_from || node_to < from) {
            return 0;
        }
        int mid = (node_from + node_to) / 2;
        return query(from, to, left(node), node_from, mid) +
               query(from, to, right(node), mid + 1, node_to);
    }

    T query(int from, int to) { return query(from, to, 1, 0, n - 1); }

    void update(int from, int to, T d, int node, int node_from, int node_to) {
        if (from <= node_from && node_to <= to) {
            t[node] = d;
            return;
        }
        if (to < node_from || node_to < from) {
            return;
        }
        int mid = (node_from + node_to) / 2;
        update(from, to, d, left(node), node_from, mid);
        update(from, to, d, right(node), mid + 1, node_to);
        t[node] = t[left(node)] + t[right(node)];
    }

    void update(int from, int to, T d) {
        update(from, to, d, 1, 0, n - 1);
    }
};

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int64_t> x(n);

    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    SegmentTree<int64_t> st(x, 0);

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int pos, val;
            cin >> pos >> val;
            pos--;
            st.update(pos, pos, val);

        } else {
            int from, to;
            cin >> from >> to;
            from--; to--;
            cout << st.query(from, to) << '\n';
        }
    }

    return 0;
}
