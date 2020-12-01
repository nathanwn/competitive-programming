/// Tested here: https://judge.yosupo.jp/submission/31022

#ifndef DSU_H_
#define DSU_H_

struct DSU {
    int n;
    vector<int> p;
    vector<int> d;

    DSU(int n) : n(n) {
        p.resize(n);
        d.resize(n, 0);
        for (int i = 0; i < n; i++) p[i] = i;
    }

    int get(int u) {
        while (u != p[u]) u = p[u];
        return u;
    }

    bool merge(int u, int v) {
        u = get(u), v = get(v);
        if (u == v) return false;

        if (d[u] > d[v]) {
            p[v] = u;
        } else {
            p[u] = v;
            if (d[u] == d[v]) d[v]++;
        }
        return true;
    }
};

#endif // DSU_H_
