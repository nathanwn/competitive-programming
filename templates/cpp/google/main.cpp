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

template <typename T> T ceilDiv(T a, T x) { return (a + x - 1) / x; }
template <typename T> void umin(T& a, T b) { a = min(a, b); }
template <typename T> void umax(T& a, T b) { a = max(a, b); }

struct Solver {
    Solver() {

    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        cout << "Case #" << ti << ": ";
        Solver solver;
    }

    return 0;
}
