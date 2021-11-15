#include <bits/stdc++.h>

using namespace std;

const int inf = (int) 1e9;
const vector<int> dr = {-1, 0, 0, 1};
const vector<int> dc = {0, -1, 1, 0};
const vector<char> steps = {'U', 'L', 'R', 'D'};
const int D = 4;

struct Solver {
    int n, m;
    vector<string> g;
    vector<vector<int>> delta;
    vector<vector<int>> visited;
    vector<vector<char>> taken;

    bool dfs(int r, int c, int t) {
        visited[r][c]++;

        if (t >= delta[r][c]) {
            visited[r][c]--;
            return false;
        }

        if (r == 0 || r == n - 1 || c == 0 || c == m - 1) return true;

        for (int i = 0; i < D; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            if (g[nr][nc] == '#' || visited[nr][nc]) continue;
            taken[r][c] = steps[i];
            if (dfs(nr, nc, t + 1)) return true;
        }

        visited[r][c]--;
        return false;
    }

    // delta[i][j] = min time for any monster to reach (i, j)
    void calcDelta() {
        queue<pair<int, int>> q;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (g[r][c] == 'M') {
                    q.push({r, c});
                    delta[r][c] = 0;
                }
            }
        }

        while (!q.empty()) {
            pair<int, int> cur = q.front(); q.pop();
            int r = cur.first;
            int c = cur.second;

            for (int i = 0; i < D; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if (g[nr][nc] == '#') continue;
                if (delta[r][c] + 1 < delta[nr][nc]) {
                    delta[nr][nc] = delta[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    Solver() {
        cin >> n >> m;
        g.resize(n);
        delta.assign(n, vector<int>(m, inf));
        visited.assign(n, vector<int>(m, 0));
        taken.assign(n, vector<char>(m));

        for (int r = 0; r < n; r++) {
            cin >> g[r];
        }

        int sr = -1;
        int sc = -1;

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (g[r][c] == 'A') {
                    sr = r;
                    sc = c;
                    break;
                }
            }
            if (sr != -1) break;
        }

        calcDelta();

        vector<char> path;

        if (dfs(sr, sc, 0)) {
            int r = sr;
            int c = sc;
            while (!(r == 0 || r == n - 1 || c == 0 || c == m - 1)) {
                for (int i = 0; i < D; i++) {
                    if (steps[i] == taken[r][c]) {
                        r += dr[i];
                        c += dc[i];
                        path.push_back(steps[i]);
                        break;
                    }
                }
            }

            cout << "YES\n";
            cout << path.size() << '\n';
            for (char x : path) cout << x;
            cout << '\n';
        } else {
            cout << "NO\n";
        }
    }
};

int main() {
    Solver solver;
    return 0;
}
