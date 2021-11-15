#include <bits/stdc++.h>

using namespace std;

template <typename T>
int sgn(T val) {
    if (val < 0) return -1;
    if (val > 0) return 1;
    return 0;
}

template <typename T>
struct Point {
    using P=Point;
    T x, y;

    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    P operator+(P o) const { return P(x + o.x, y + o.y); }
    P operator-(P o) const { return P(x - o.x, y - o.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P o) const { return x * o.x + y * o.y; }
    T cross(P o) const { return x * o.y - y * o.x; }
    T abs2() const { return x * x + y * y; }
    long double abs() const { return sqrt((long double) abs2()); }
    double angle() const { return atan2(y, x); } // [-pi, pi]
    P unit() const { return *this / abs(); } // makes abs()=1
    P perp() const { return P(-y, x); } // rotates +pi/2

    P rotate(double a) const { // ccw
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

using P = Point<int64_t>;

bool colinear(const P& v1, const P& v2) {
    return v1.cross(v2) == 0;
}

bool checkBoundingBox(
        const P& p1,
        const P& q1,
        const P& p2,
        const P& q2
) {
    if (max(p1.x, q1.x) < min(p2.x, q2.x)) return true;
    if (max(p1.y, q1.y) < min(p2.y, q2.y)) return true;
    if (max(p2.x, q2.x) < min(p1.x, q1.x)) return true;
    if (max(p2.x, q2.x) < min(p1.x, q1.x)) return true;
    return false;
}

int main() {
    int n;
    cin >> n;

    vector<P> polygon;

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        polygon.emplace_back(x, y);
    }

    int64_t area = 0;

    for (int i = 0; i < n; i++) {
        P p1 = polygon[i];
        P p2 = polygon[(i + 1) % n];
        area += p1.cross(p2);
    }

    cout << abs(area) << '\n';

    return 0;
}
