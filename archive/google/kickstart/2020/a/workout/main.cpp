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

struct Segment {
    int from;
    int to;
    int subsegment;

    Segment(int f, int t) : from(f), to(t), subsegment(1) {}

    int len() const {
        return (to - from) / subsegment;
    }

    bool operator<(const Segment& o) const {
        return len() > o.len();
    }

    bool saturated() const {
        return to - from == subsegment;
    }

};

struct Solver {
    Solver() {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        priority_queue<Segment> pq;

        for (int i = 1; i < n; i++) {
            pq.emplace(a[i - 1], a[i]);
        }

        for (int j = 0; j < k; j++) {
            while (!pq.empty() && pq.top().saturated()) pq.pop();
            if (pq.empty()) {
                cout << "1\n";
                return;
            }
            Segment s = pq.top();
            pq.pop();
            s.subsegment++;
            pq.push(s);
        }

        cout << pq.top().len() << '\n';
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
