/// Warning: not tested!

#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_

template <typename T>
class SegmentTree {
    /// Each node manages the range [nfrom, nto]
    /// Each query ask for the range [from, to]
    int n;
    vector<T> value;
    vector<T> lazy;
    function<T(T, T)> fMerge;
    function<T(T, T)> fUpdate;
    T defaultValue;
    T defaultLazy;

    int left(int node)  { return 2 * node + 1; }
    int right(int node) { return 2 * node + 2; }

    void apply(int node, int delta) {
        value[node] = fUpdate(value[node], delta);
        lazy[node] = fUpdate(lazy[node], delta);
    }

    void pushDown(int node) {
        apply(left(node), lazy[node]);
        apply(right(node), lazy[node]);
        lazy[node] = defaultLazy;
    }

    void build(vector<int>& a, int node, int nfrom, int nto) {
        if (nfrom == nto) {
            value[node] = a[nfrom];
            return;
        }

        int nmid = (nfrom + nto) / 2;
        build(a, left(node), nfrom, nmid);
        build(a, right(node), nmid + 1, nto);
        value[node] = fMerge(value[left(node)], value[right(node)]);
    }

    T query(int from, int to, int node, int nfrom, int nto) {
        if (from <= nfrom && nto <= to) return value[node];
        if (to < nfrom || nto < from) return defaultValue;

        pushDown(node);

        int nmid = (nfrom + nto) / 2;
        return fMerge(
            query(from, to, left(node), nfrom, nmid),
            query(from, to, right(node), nmid + 1, nto)
        );
    }

    void update(int from, int to, T delta, int node, int nfrom, int nto) {
        if (from > to) return;

        if (from == nfrom && to == nto) {
            apply(node, delta);
            return;
        }

        pushDown(node);

        int nmid = (nfrom + nto) / 2;
        update(from, to, delta, left(node), nfrom, nmid);
        update(from, to, delta, right(node), nmid + 1, nto);

        value[node] = fMerge(value[left(node)], value[right(node)]);
    }

public:
    SegmentTree(vector<int>& a, function<T(T, T)> fMerge, function<T(T, T)> fUpdate, T defaultValue, T defaultLazy) :
        fMerge(fMerge), fUpdate(fUpdate), defaultValue(defaultValue), defaultLazy(defaultLazy) {
        n = a.size();
        value.resize(n * 4);
        lazy.resize(n * 4, defaultLazy);
        build(a, 0, 0, n - 1);
    }

    T query(int from, int to) { return query(from, to, 0, 0, n - 1); }

    void update(int from, int to, T delta) { update(from, to, delta, 0, 0, n - 1); }
};

#endif // SEGMENT_TREE_H_
