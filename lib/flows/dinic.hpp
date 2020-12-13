/**
 * Tested here: https://cses.fi/problemset/task/1694/
**/

#pragma once

#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct FlowEdge {
    int u, v;
    T c, f;

    FlowEdge(int _u, int _v, T _c, T _f) :
        u(_u), v(_v), c(_c), f(_f) {}
};

template <typename T>
struct Dinic {
    const T inf = numeric_limits<T>::max();
    const T eps = (T) 1e-9;
    int n;
    int s, t;
    vector<vector<int>> adj; // stores indices of edges
    vector<int> level;       // shortest distance from source
    vector<int> ptr;         // points to the next edge which can be used
    vector<FlowEdge<T>> edges;

    Dinic(int _n, int _s, int _t)
        : n(_n), s(_s), t(_t), adj(_n), level(_n), ptr(_n) {}

    void addEdge(int u, int v, int c, int rc=0) {
        int eid = (int) edges.size();
        adj[u].push_back(eid);
        adj[v].push_back(eid + 1);
        edges.emplace_back(u, v, c, 0);
        edges.emplace_back(v, u, rc, 0);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int eid : adj[u]) {
                const auto& e = edges[eid];
                if (e.c - e.f <= eps || level[e.v] != -1) continue;
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }

        return level[t] != -1;
    }

    T dfs(int u, T flow) {
        if (u == t) return flow;

        for (int& j = ptr[u]; j < (int) adj[u].size(); j++) {
            int eid = adj[u][j];
            const auto& e = edges[eid];
            if (e.c - e.f > eps && level[e.v] == level[u] + 1) {
                T df = dfs(e.v, min(e.c - e.f, flow));
                if (df > eps) {
                    edges[eid].f += df;
                    edges[eid ^ 1].f -= df;
                    return df;
                }
            }
        }

        return 0;
    }

    T maxFlow() {
        T f = 0;

        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            T totalDf = 0;
            while (true) {
                T df = dfs(s, inf);
                if (df <= eps) break;
                totalDf += df;
            }
            if (totalDf <= eps) {
                break;
            }
            f += totalDf;
        }

        return f;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    flow_graph<int64_t> g(n, 0, n - 1);
    Dinic<int64_t> meSolver(n, 0, n - 1);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        g.add(u, v, c, 0);
        meSolver.addEdge(u, v, c);
    }

    dinic<int64_t> solver(g);

    cout << meSolver.maxFlow() << '\n';

    return 0;
}
