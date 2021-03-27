#include <bits/stdc++.h>

using namespace std;

string to_string(string s)      { return '"' + s + '"';          }
string to_string(const char* s) { return to_string((string) s);  }
string to_string(bool b)        { return (b ? "true" : "false"); }

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());

template <typename T> void minimize(T& a, T b) { a = min(a, b); }
template <typename T> void maximize(T& a, T b) { a = max(a, b); }

struct Solver {
    int n, c;
    vector<int> a;
    vector<int> p;
    vector<bool> used;
    bool possible;

    int cost() {
        vector<int> x = p;
        int ans = 0;

        for (int i = 0; i < n - 1; i++) {
            int min_id = i;

            for (int j = i + 1; j < n; j++) {
                if (x[j] < x[min_id]) {
                    min_id = j;
                }
            }

            reverse(x.begin() + i, x.begin() + min_id + 1);
            ans += min_id - i + 1;
        }

        return ans;
    }

    void backtrack(int id) {
        if (possible) return;

        if (id == n) {
            if (cost() == c) {
                for (int e : p) {
                    cout << e << ' ';
                }
                cout << '\n';
                possible = true;
            }
            return;
        }

        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                p[id] = a[i];
                used[i] = true;
                backtrack(id + 1);
                used[i] = false;
            }
        }
    }

    Solver() {
        cin >> n >> c;
        debug(n, c);
        a.resize(n);
        p.resize(n);
        used.assign(n, false);
        possible = false;

        for (int i = 0; i < n; i++) {
            a[i] = i + 1;
        }

        backtrack(0);

        if (!possible) cout << "IMPOSSIBLE\n";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        Solver solver;
    }

    return 0;
}
