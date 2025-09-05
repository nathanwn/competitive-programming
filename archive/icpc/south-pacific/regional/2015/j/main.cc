#include <bits/stdc++.h>

using namespace std;

/// Note: I stole this Point struct from KTH's notebook, but for
/// this solution to be accepted I had to change the abs() method
/// return type from `double` to `long double`

template <typename T>
struct Point {
    using P=Point;
    T x, y;

    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    P operator+(P o) const { return P(x + o.x, y + o.y); }
    P operator-(P o) const { return P(x - o.x, y - o.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P o) const { return x * o.x + y * o.y; }
    T cross(P o) const { return x * o.y - y * o.x; }
	T abs2() const { return x * x + y * y; }
    long double abs() const { return sqrt((long double) abs2()); }
    double angle() const { return atan2(y, x); } // [-pi, pi]
	P unit() const { return *this / abs(); } // makes abs()=1
	P perp() const { return P(-y, x); } // rotates +pi/2

	P rotate(double a) const { // ccw
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << ", " << p.y << ")";
    }
};

template <typename T=long double>
struct Circle {
    Point<T> p;
    T r;

    Circle() {}
    Circle(T _x, T _y, T _r) : p(_x, _y), r(_r) {}

    T distance(const Circle& other) const {
        Point<T> vec = p - other.p;
        return vec.abs() - r - other.r;
    }

    T innerDistance(const Circle& outer) const {
        Point<T> vec = p - outer.p;
        return outer.r - (vec.abs() + r);
    }
};

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
            if (totalDf <= eps) break;
            f += totalDf;
        }

        return f;
    }
};

struct Solver {
    int lakeRadius, islandRadius, n;
    Circle<> lake;
    Circle<> island;
    vector<Circle<>> stones;

    Solver() {
        cin >> lakeRadius >> islandRadius >> n;
        lake = Circle<>(0, 0, lakeRadius);
        island = Circle<>(0, 0, islandRadius);
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            stones.emplace_back(x, y, 1);
        }
    }

    bool isSafe(int step) {
        const long double eps = 1e-9;

        // [0..n - 1]: from nodes; [n..2n - 1]: to nodes
        // s = 2n = lake edge; t = 2n + 1 = island

        int s = 2 * n;
        int t = 2 * n + 1;
    
        // Change Dinic to EdmondsKarp if you want to try
        Dinic<int> maxFlowSolver(2 * n + 2, s, t);
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (stones[i].distance(stones[j]) <= step) {
                    maxFlowSolver.addEdge(i, j + n, 1);
                    maxFlowSolver.addEdge(j, i + n, 1);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (stones[i].innerDistance(lake) <= step) {
                maxFlowSolver.addEdge(s, i + n, 1);
            }

            if (island.distance(stones[i]) <= step) {
                maxFlowSolver.addEdge(i, t, 1);
            }

            maxFlowSolver.addEdge(i + n, i, 1);
        }

        int maxFlow = maxFlowSolver.maxFlow();

        return maxFlow >= 4;
    }

    void solve() {
        int left = 0;
        int right = lakeRadius - islandRadius;

        int ans = -1;

        while (left <= right) {
            int mid = (right - left) / 2 + left;
            if (isSafe(mid)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        assert(ans != -1);
        cout << ans << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Solver solver;
    solver.solve();

    return 0;
}
