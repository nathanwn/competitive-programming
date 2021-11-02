#include <bits/stdc++.h>

using namespace std;

const int mod = (int) 1e9 + 7;

int modAdd(int& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

const int N = 2000;
int strfree[N + 1][N + 1];
int strful[N + 1][N + 1];

void preCalcDP() {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            strfree[i][j] = 0;
            strful[i][j] = 0;
        }
    }

    strfree[1][0] = 1;
    strful[0][0] = 1;

    // i = our score, j = opponent's score
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (j >= 1 && i > j) modAdd(strfree[i][j], strfree[i][j - 1]);
            if (i >= 1 && i - 1 > j) modAdd(strfree[i][j], strfree[i - 1][j]);
            if (j >= 1 && i <= j - 1) modAdd(strful[i][j], strful[i][j - 1]);
            if (i >= 1 && i <= j) modAdd(strful[i][j], strful[i - 1][j]);
        }
    }
}

struct Solver {
    int x, y;

    Solver() {
        scanf("%d-%d", &x, &y);
        printf("%d %d\n", strfree[x][y], strful[y][y]);
    }
};

int main() {
    preCalcDP();

    int t;
    scanf("%d", &t);

    for (int ti = 1; ti <= t; ti++) {
        printf("Case #%d: ", ti);
        Solver solver;
    }

    return 0;
}
