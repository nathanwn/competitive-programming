#include <bits/stdc++.h>

using namespace std;

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

int main() {
    int t;
    cin >> t;

    for (int ti = 0; ti < t; ti++) {
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        P p1(x1, y1);
        P p2(x2, y2);
        P p3(x3, y3);
        p2 = p2 - p1;
        p3 = p3 - p1;
        if (p2.cross(p3) > 0) {
            cout << "LEFT\n";
        } else if (p2.cross(p3) < 0) {
            cout << "RIGHT\n";
        } else {
            cout << "TOUCH\n";
        }
    }

    return 0;
}
