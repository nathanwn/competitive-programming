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
struct EdmondsKarp {
    const T inf = numeric_limits<T>::max();
    int n;
    int s, t;
    vector<vector<int>> adj; // stores indices of edges
    vector<int> path;
    vector<FlowEdge<T>> edges;

    EdmondsKarp(int _n, int _s, int _t)
        : n(_n), s(_s), t(_t), adj(_n), path(_n) {}

    void addEdge(int u, int v, int c, int rc=0) {
        int eid = (int) edges.size();
        adj[u].push_back(eid);
        adj[v].push_back(eid + 1);
        edges.emplace_back(u, v, c, 0);
        edges.emplace_back(v, u, rc, 0);
    }

    T augPath() {
        fill(path.begin(), path.end(), -1);
        path[s] = -2;
        queue<pair<int, T>> q;
        q.emplace(s, inf);

        while (!q.empty()) {
            int u = q.front().first;
            T flow = q.front().second;
            q.pop();

            for (int eid : adj[u]) {
                int v = edges[eid].v;
                T c = edges[eid].c;

                if (path[v] == -1 && c > 0) {
                    path[v] = eid;
                    flow = min(flow, c);
                    if (v == t) return flow;
                    q.emplace(v, flow);
                }
            }
        }

        return 0;
    }

    T maxFlow() {
        T f = 0;

        while (true) {
            T df = augPath();
            if (df == 0) break;

            f += df;
            int v = t;

            while (path[v] != -2) {
                int eid = path[v];
                edges[eid].c -= df;
                edges[eid ^ 1].c += df;
                v = edges[eid].u;
            }
        }

        return f;
    }
};
