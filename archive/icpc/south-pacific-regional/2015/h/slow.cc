#include <bits/stdc++.h>

using namespace std;

const int64_t INF = LONG_MAX;
const int N = 50;
int64_t d[N * N][N * N];
int h, w;

int64_t ceilDiv(int64_t a, int64_t x) {
    return (a + x - 1) / x;
}

int cell(int i, int j) {
    if (i < 0 || i >= h) return -1;
    if (j < 0 || j >= w) return -1;
    return i * w + j;
}

int west(int i, int j) {
    return cell(i, j - 1);
}

int east(int i, int j) {
    return cell(i, j + 1);
}

int north(int i, int j) {
    return cell(i - 1, j);
}

int south(int i, int j) {
    return cell(i + 1, j);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> h >> w;

    int n = h * w;

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            d[u][v] = INF;
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int c;
            cin >> c;
            int u = cell(i, j);
            int v = north(i, j);
            if (v != -1) d[u][v] = c;
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int c;
            cin >> c;
            int u = cell(i, j);
            int v = west(i, j);
            if (v != -1) d[u][v] = c;
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int c;
            cin >> c;
            int u = cell(i, j);
            int v = south(i, j);
            if (v != -1) d[u][v] = c;
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int c;
            cin >> c;
            int u = cell(i, j);
            int v = east(i, j);
            if (v != -1) d[u][v] = c;
        }
    }


    for (int k = 0; k < n; k++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (d[u][k] != INF && d[k][v] != INF) {
                    d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
                }
            }
        }
    }

    int64_t sum = 0;

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u == v) continue;
            sum += d[u][v];
        }
    }

    int64_t avg = ceilDiv(sum, n * (n - 1));
    cout << avg << '\n';

    return 0;
}
