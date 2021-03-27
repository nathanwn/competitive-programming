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

const int INF = 1e9;

struct Solver {
    int x, y;
    int n;
    string s;
    string t;
    int ans;

    void backtrack(int i) {
        if (i == n) {
            int cur = 0;
            for (int j = 0; j < n - 1; j++) {
                if (t[j] == 'C' && t[j + 1] == 'J') {
                    cur += x;
                } else if (t[j] == 'J' && t[j + 1] == 'C') {
                    cur += y;
                }
            }
            ans = min(ans, cur);
        } else {
            if (s[i] == '?') {
                t[i] = 'C';
                backtrack(i + 1);
                t[i] = 'J';
                backtrack(i + 1);
            } else {
                t[i] = s[i];
                backtrack(i + 1);
            }
        }
    }

    Solver() {
        cin >> x >> y;
        cin >> s;
        n = s.length();
        ans = INF;
        t.resize(n);

        backtrack(0);
        cout << ans << '\n';
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
