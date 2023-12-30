#include <bits/stdc++.h>

using namespace std;

template <typename T>
int sgn(T x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

int inc(int i, int n, int by=1) {
    i += by;
    if (i >= n) i -= n;
    return i;
}

template<typename T>
struct Point {
    using P = Point;
    T x, y;

    Point(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}

    P operator+(const P &o) const { return P(x + o.x, y + o.y); }

    P operator-(const P &o) const { return P(x - o.x, y - o.y); }

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

    friend istream &operator>>(istream &is, P &p) {
        return is >> p.x >> p.y;
    }

    friend ostream &operator<<(ostream &os, P &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }

    // position of c relative to a->b
    // > 0: c is on the left of a->b
    friend T orient(P a, P b, P c) {
        return (b - a).cross(c - a);
    }

    // Check if two vectors u and v are parallel (u = cv where c in R)
    friend bool parallel(P u, P v) {
        return u.cross(v) == 0;
    }

    // Check if point p lies on the segment ab
    friend bool onSegment(P a, P b, P p) {
        return orient(a, b, p) == 0 &&
               min(a.x, b.x) <= p.x &&
               max(a.x, b.x) >= p.x &&
               min(a.y, b.y) <= p.y &&
               max(a.y, b.y) >= p.y;
    }

    friend bool boundingBox(P p1, P q1, P p2, P q2) {
        if (max(p1.x, q1.x) < min(p2.x, q2.x)) return true;
        if (max(p1.y, q1.y) < min(p2.y, q2.y)) return true;
        if (max(p2.x, q2.x) < min(p1.x, q1.x)) return true;
        if (max(p2.x, q2.x) < min(p1.x, q1.x)) return true;
        return false;
    }

    friend bool intersect(P p1, P p2, P p3, P p4) {
        // Check if two segments are parallel
        if (parallel(p2 - p1, p4 - p3)) {
            // Check if 4 ps are colinear
            if (!parallel(p2 - p1, p3 - p1)) return false;
            if (boundingBox(p1, p2, p3, p4)) return false;
            return true;
        }

        // check if one line is completely on one side of the other
        for (int i = 0; i < 2; i++) {
            if (sgn((p2 - p1).cross(p3 - p1)) == sgn((p2 - p1).cross(p4 - p1))
                && sgn((p2 - p1).cross(p3 - p1)) != 0) {
                return false;
            }
            swap(p1, p3);
            swap(p2, p4);
        }
        return true;
    }

    // Check if the point p is in the angle (bac) (including the rays)
    friend bool inAngle(P a, P b, P c, P p) {
        assert(orient(a, b, c) != 0);
        if (orient(a, b, c) < 0) swap(b, c);
        return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
    }
};

template <typename T>
struct Polygon {
    using P = Point<T>;

    int n = 0;
    vector<P> ps;
    Polygon() : n(0) {}
    Polygon(vector<P>& ps) : n(ps.size()), ps(ps) {}

    void add(P p) {
        ps.push_back(p);
        n++;
    }

    int64_t twiceArea() {
        int64_t area = 0;
        for (int i = 0; i < n; i++) {
            P p1 = ps[i];
            P p2 = ps[inc(i, n)];
            area += p1.cross(p2);
        }
        return abs(area);
    }

    double area() {
        return twiceArea() / 2.0;
    }

    int64_t boundaryLattice() {
        int64_t res = 0;
        for (int i = 0; i < n; i++) {
            int j = i + 1; if (j == n) j = 0;
            P p1 = ps[i];
            P p2 = ps[j];
            P v = p2 - p1;
            res += __gcd(abs(v.x), abs(v.y));
        }
        return res;
    }

    int64_t interiorLattice() {
        return (twiceArea() - boundaryLattice()) / 2 + 1;
    }

    bool isConvex() {
        int pos = 0;
        int neg = 0;

        for (int i = 0; i < n; i++) {
            P p1 = ps[i];
            P p2 = ps[inc(i, n, 1)];
            P p3 = ps[inc(i, n, 2)];
            int o = orient(p1, p2, p3);
            if (o > 0) pos = 1;
            if (o < 1) neg = 1;
        }

        return pos ^ neg;
    }

    // -1: outside; 1: inside; 0: on boundary
    int vsPoint(P r) {
        int crossing = 0;
        for (int i = 0; i < n; i++) {
            P p1 = ps[i];
            P p2 = ps[inc(i, n)];
            if (onSegment(p1, p2, r)) {
                return 0;
            }
            if (((p2.y >= r.y) - (p1.y >= r.y)) * orient(r, p1, p2) > 0) {
                crossing++;
            }
        }
        if (crossing & 1) return 1;
        return -1;
    }
};

template <typename T>
Polygon<T> convexHull(vector<Point<T>> points) {
    using P = Point<T>;

    sort(points.begin(), points.end(),
         [](const P& p1, const P& p2) {
             if (p1.x == p2.x) return p1.y < p2.y;
             return p1.x < p2.x;
         });

    vector<P> hull;

    for (int step = 0; step < 2; step++) {
        int s = hull.size();
        for (const P& c : points) {
            while ((int) hull.size() - s >= 2) {
                P a = hull.end()[-2];
                P b = hull.end()[-1];
                // change to <= if points on the edges are accepted
                if (orient(a, b, c) <= 0) break;
                hull.pop_back();
            }
            hull.push_back(c);
        }
        hull.pop_back();
        reverse(points.begin(), points.end());
    }

    return Polygon<T>(hull);
}

using Polygon64 = Polygon<int64_t>;
using Point64 = Point<int64_t>;

struct Solver {
    void solve() {
        int n;
        cin >> n;
        vector<Point64> points;

        for (int i = 0; i < n; i++) {
            Point64 p; cin >> p;
            points.push_back(p);
        }

        Polygon64 hull = convexHull(points);

        cout << hull.n << '\n';

        for (const Point64& p : hull.ps) {
            cout << p.x << ' ' << p.y << '\n';
        }
    }
};

int main() {
    Solver solver;
    solver.solve();
    return 0;
}
