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

    Solver() {
        cin >> x >> y;
        cin >> s;
        n = s.length();

        const int C = 0;
        const int J = 1;
        vector<vector<int>> dp(2, vector<int>(n));
        // dp[C][j]: min cost of string s[0..j] when s[j] is 'C'
        // dp[J][j]: min cost of string s[0..j] when s[j] is 'J'

        if (s[0] == 'C') {
            dp[C][0] = 0;
            dp[J][0] = INF;
        } else if (s[0] == 'J') {
            dp[C][0] = INF;
            dp[J][0] = 0;
        } else {
            dp[C][0] = 0;
            dp[J][0] = 0;
        }

        for (int i = 1; i < n; i++) {
            if (s[i] == 'C') {
                dp[C][i] = min(dp[C][i - 1], dp[J][i - 1] + y);
                dp[J][i] = INF;
            } else if (s[i] == 'J') {
                dp[C][i] = INF;
                dp[J][i] = min(dp[J][i - 1], dp[C][i - 1] + x);
            } else {
                dp[C][i] = min(dp[C][i - 1], dp[J][i - 1] + y);
                dp[J][i] = min(dp[J][i - 1], dp[C][i - 1] + x);
            }
        }

        int ans = min(dp[C][n - 1], dp[J][n - 1]);
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
