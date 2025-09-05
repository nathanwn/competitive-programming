#include <bits/stdc++.h>

using namespace std;

const int N = 1e5;

struct Edge {
    int u, v ,w;

    Edge(int u_, int v_, int w_) : u(u_), v(v_), w(w_) {}
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> cnt(N + 1, 0);

    for (int i = 0; i < 3 * m; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    vector<Edge> edges;

    int v = 1;
    int max_u = n;
    int min_w = 0;

    for (int i = 0; i < m; i++) {
        while (cnt[max_u] == 0) max_u--;
        while (cnt[min_w] == 0) min_w++;
        cnt[max_u]--;
        cnt[v]--;
        cnt[min_w]--;
        edges.emplace_back(max_u, v, min_w);
    }

    for (const Edge& e : edges) {
        cout << e.u << ' ' << e.v << ' ' << e.w << '\n';
    }

    return 0;
}
