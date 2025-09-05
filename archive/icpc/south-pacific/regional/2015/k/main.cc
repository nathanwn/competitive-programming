#include <bits/stdc++.h>

using namespace std;

int toDec(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'Z') return c - 'A' + 10;
    return c - 'a' + 10 + 26;
}

int toDec(char* s) {
    return toDec(s[0]) * 62 * 62 + toDec(s[1]) * 62 + toDec(s[2]);
}

struct Stadium {
    int city;
    int from;
    int to;

    Stadium(int city_, int from_, int to_) :
        city(city_), from(from_), to(to_) {}
};

struct Solver {
    int n;
    vector<Stadium> stadiums;

    Solver(int _n) : n(_n) {
        char s[10];

        for (int i = 0; i < n; i++) {
            cin >> s;
            int from = toDec(s);
            int to = toDec(s + 3);
            stadiums.emplace_back(i, from, to);
        }
    }

    bool isGreat(int from, int to) {
        if (to - from + 1 <= 1) {
            return true;
        }

        for (int i = from, j = to; i <= j; i++, j--) {
            if (stadiums[i].from <= from && to <= stadiums[i].to) {
                return isGreat(from, stadiums[i].city - 1)
                    && isGreat(stadiums[i].city + 1, to);
            }

            if (stadiums[j].from <= from && to <= stadiums[j].to) {
                return isGreat(from, stadiums[j].city - 1)
                    && isGreat(stadiums[j].city + 1, to);
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

    while (cin >> n) {
        Solver solver(n);
        solver.solve();
    }

    return 0;
}
