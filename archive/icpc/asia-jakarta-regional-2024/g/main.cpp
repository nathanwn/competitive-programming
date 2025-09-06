#include <cstdint>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

template <typename T>
struct vec2d : public vector<vector<T>> {
    explicit vec2d(int n0=0, int n1=0, T t=T())
    : vector<vector<T>>(n0, vector<T>(n1, t)) {}
};

template <typename T>
struct vec3d : public vector<vec2d<T>> {
    explicit vec3d(int n0=0, int n1=0, int n2=0, T t=T())
    : vector<vec2d<T>>(n0, vec2d<T>(n1, n2, t)) {}
};

struct PQEntry {
    int r, c;
    int64_t w;
    PQEntry(int r_, int c_, int64_t w_) : r(r_), c(c_), w(w_) {}

    bool operator<(const PQEntry& o) const {  // min-heap
        return w > o.w;
    }
};

int D = 4;
int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < m; j++) {
            g[i][j] = row[j] - '0';
        }
    }

    int nq;
    cin >> nq;
    vector<array<int, 4>> qs;

    for (int qi = 0; qi < nq; qi++) {
        int sr, sc, tr, tc;
        cin >> sr >> sc >> tr >> tc;
        sr--; sc--; tr--; tc--;
        qs.push_back({sr, sc, tr, tc});
    }

    vec3d<int64_t> w(n, m, D);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int d = 0; d < D; d++) {
                int a = i + dr[d];
                int b = j + dc[d];
                if (a < 0 || a >= n) continue;
                if (b < 0 || b >= m) continue;

                w[i][j][d] = 1;
                for (int c = 0; c < k; c++) {
                    w[i][j][d] *= (g[a][b] - g[i][j]);
                }
            }
        }
    }

    auto checkCycle = [&](int r, int c) -> bool {
        int64_t dis = w[r][c][0];
        dis += w[r][c + 1][1];
        dis += w[r + 1][c + 1][2];
        dis += w[r + 1][c][3];
        return dis == 0;
    };

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (!checkCycle(i, j)) {
                for (int qi = 0; qi < nq; qi++) {
                    cout << "INVALID\n";
                }
                return 0;
            }
        }
    }

    const int64_t INF = (int64_t) 1e18 + 26;
    vec2d<int64_t> dis(n, m);
    vec2d<bool> vis(n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dis[i][j] = INF;
            vis[i][j] = false;
        }
    }

    priority_queue<PQEntry> pq;
    pq.emplace(0, 0, 0);
    dis[0][0] = 0;

    while (!pq.empty()) {
        PQEntry u = pq.top();
        pq.pop();

        if(vis[u.r][u.c]) continue;
        vis[u.r][u.c] = true;

        for(int i = 0; i < D; i++) {
            int vr = u.r + dr[i];
            int vc = u.c + dc[i];
            int64_t vw = u.w + w[u.r][u.c][i];
            if(0 <= vr && vr < n && 0 <= vc && vc < m && dis[vr][vc] > vw) {
                dis[vr][vc] = vw;
                pq.emplace(vr, vc, vw);
            }
        }
    }

    for (int i = 0; i < nq; i++) {
        int sr = qs[i][0];
        int sc = qs[i][1];
        int tr = qs[i][2];
        int tc = qs[i][3];
        cout << (dis[sr][sc] - dis[tr][tc]) << "\n";
    }

    return 0;
}
