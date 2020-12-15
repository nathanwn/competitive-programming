#include <bits/stdc++.h>

using namespace std;

char buf[10];

int base62ToDec(char c) {
    if ('0' <= c && c <= '9') {
        return c - '0';
    }
    if ('A' <= c && c <= 'Z') { 
        return c - 'A' + 10;
    }
    assert('a' <= c && c <= 'z');
    return c - 'a' + 10 + 26;
}

struct Stadium {
    int city;
    int from;
    int to;

    Stadium(int city_, int from_, int to_) :
        city(city_), from(from_), to(to_) {
    }
};

struct Solver {
    int n;
    vector<Stadium> stadiums;

    Solver(int _n) : n(_n) {
        for (int i = 0; i < n; i++) {
            assert(scanf("%s", buf) != EOF);
            int from = base62ToDec(buf[0]) * 3844 + base62ToDec(buf[1]) * 62 + base62ToDec(buf[2]);
            int to = base62ToDec(buf[3]) * 3844 + base62ToDec(buf[4]) * 62 + base62ToDec(buf[5]);
            stadiums.emplace_back(i, from, to);
        }
    }

    bool isGreat(int from, int to) {
        if (to - from + 1 <= 1) {
            return true;
        }

        for (int i = from; i <= to; i++) {
            if (stadiums[i].from <= from && to <= stadiums[i].to) {
                return isGreat(from, stadiums[i].city - 1)
                    && isGreat(stadiums[i].city + 1, to);
            }
        }

        return false;
    }

    void solve() {
        bool isBad = true;
        for (const auto& stadium : stadiums) {
            if (stadium.from <= 0 && n - 1 <= stadium.to) {
                isBad = false;
                break;
            }
        }

        if (isBad) {
            cout << "Bad\n";
            return;
        }

        if (isGreat(0, n - 1)) {
            cout << "Great\n";
        } else {
            cout << "Acceptable\n";
        }
    }
};

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        Solver solver(n);
        solver.solve();
    }

    return 0;
}
