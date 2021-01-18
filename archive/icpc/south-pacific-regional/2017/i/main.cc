#include <bits/stdc++.h>

using namespace std;

struct SegmentTree {
    using T = int;

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
        if (t[u].is_lazy) {
            t[left(u)].val = t[right(u)].val = t[u].val;
            t[left(u)].is_lazy = t[right(u)].is_lazy = true;
            t[u].is_lazy = false;
        }
    }

    T query(int from, int to, int u=0) {
        if (from <= t[u].from && t[u].to <= to) return t[u].val;
        if (to < t[u].from || t[u].to < from) return dquery;
        pushDown(u);
        return merge(query(from, to, left(u)), query(from, to, right(u)));
    }

    void apply(int u, T delta) {
        t[u].val = delta;
        t[u].is_lazy = true;
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

struct SuffixArray {
    string s;
    const int alpha;
    int n;

    SuffixArray(const string& s_, int alpha_=256) :
        s(s_ + '\0'), alpha(alpha_), n(s.size()) {}

    vector<int> get() {
        vector<int> p(n);
        vector<int> cnt(max(alpha, n), 0);

        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < alpha; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;

        vector<int> g(n);
        g[p[0]] = 0;

        for (int i = 1; i < n; i++) {
            g[p[i]] = g[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
        }

        vector<int> pn(n);
        vector<int> gn(n);

        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - len; // transfer the pos from second to pair
                if (pn[i] < 0) pn[i] += n; // cyclic
            }

            int num_groups = g[p[n - 1]] + 1;
            fill(cnt.begin(), cnt.begin() + num_groups, 0);

            // Radix sort
            for (int i = 0; i < n; i++) cnt[g[pn[i]]]++;
            for (int i = 1; i < num_groups; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) p[--cnt[g[pn[i]]]] = pn[i];
            gn[p[0]] = 0;

            for (int i = 1; i < n; i++) {
                pair<int, int> prev, cur;
                prev.first = g[p[i - 1]];
                cur.first = g[p[i]];
                prev.second = g[p[i - 1] + len - (p[i - 1] + len >= n ? n : 0)];
                cur.second = g[p[i] + len - (p[i] + len >= n ? n : 0)];
                gn[p[i]] = gn[p[i - 1]] + (cur != prev);
            }
            g.swap(gn);
        }
        p.erase(p.begin());
        return p;
    }
};

int main() {
    string s;
    cin >> s;

    int n = s.length();

    vector<int> _v(n + 1, 0);
    SegmentTree seg_tree(_v);

    SuffixArray suffix_array(s);
    vector<int> sa = suffix_array.get();

    reverse(sa.begin(), sa.end());

    int toxicity = 0;
    int ans = 0;
    double max_effectiveness = 0;

    for (int i = 0; i < n; i++) {
        // let f[x] be the number of values larger than x
        toxicity += seg_tree.query(sa[i], sa[i]);
        double effectiveness = (double) i * (i + 1) / toxicity;
        if (effectiveness > max_effectiveness) {
            max_effectiveness = effectiveness;
            ans = i + 1;
        }
        seg_tree.update(0, sa[i] - 1, 1);
    }

    cout << ans << '\n';

    return 0;
}
