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

template <typename T>
struct vector2d : public vector<vector<T>> {
    vector2d(int n1=0, int n2=0, T t=T())
        : vector<vector<T>>(n1, vector<T>(n2, t)) {}
};

template <typename T>
struct vector3d : public vector<vector2d<T>> {
    vector3d(int n1=0, int n2=0, int n3=0, T t=T())
        : vector<vector2d<T>>(n1, vector2d<T>(n2, n3, t)) {}
};

template <typename T>
struct vector4d : public vector<vector3d<T>> {
    vector4d(int n1=0, int n2=0, int n3=0, int n4=0, T t=T())
        : vector<vector3d<T>>(n1, vector3d<T>(n2, n3, n4, t)) {}
};

mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());

template <typename T> T ceilDiv(T a, T x) { return (a + x - 1) / x; }

template <typename T> void minimize(T& a, T b) { a = min(a, b); }
template <typename T> void maximize(T& a, T b) { a = max(a, b); }

struct Solver {
    Solver() {
        int n, m, p;
        cin >> n >> m >> p;

        vector2d<int> a(n + 1, m + 1);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
            }
        }

        vector2d<int> ps(n + 1, m + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                ps[i][j] = a[i][j] + ps[i][j - 1];
            }
        }

        vector3d<int> dp(n + 1, m + 1, p + 1, 0);
        // dp[i][j][p]: max beauty after checking the jth dish of the ith stack
        //              and choosing p dishes

        for (int k = 1; k <= p; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j <= m; j++) {
                    if (j == 0) {
                        dp[i][j][k] = dp[i - 1][m][k];
                    }
                    else {
                        maximize(dp[i][j][k], dp[i][j - 1][k]);
                        if (k - j < 0) continue;
                        maximize(dp[i][j][k], dp[i - 1][m][k - j] + ps[i][j]);
                    }
                }
            }
        }

        cout << dp[n][m][p] << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        cout << "Case #" << ti << ": ";
        Solver solver;
    }

    return 0;
}
