#include <bits/stdc++.h>

using namespace std;

const int64_t INF = 8e18 + 1;
// largest maximum distance is between
// (-1e9, -1e9) and (1e9, 1e9), which is 8e18

struct Point {
    int x, y;
};

int64_t sq(int x) { return 1LL * x * x; }

int64_t distance(const Point& a, const Point& b) {
    return sq(a.x - b.x) + sq(a.y - b.y);
}

int64_t min_distance(const vector<Point>& ps, int low, int high) {
    // This function can be further optimized by eliminating the sort
    // reducing the complexity down to O(nlog(n)) from O(nlog^2(n))
    int n = high - low;
    if (n <= 1) {
        return INF;
    }
    int mid = low + (high - low) / 2;
    // vector<Point> left = vector<Point>(ps.begin(), ps.begin() + n / 2);
    // vector<Point> right = vector<Point>(ps.begin() + n / 2, ps.end());
    int64_t d1 = min_distance(ps, low, mid);
    int64_t d2 = min_distance(ps, mid, high);
    int64_t d = min(d1, d2);

    int mid_x = ps[mid - 1].x;
    vector<Point> stripe;
    for (int i = low; i < high; i++) {
        if (sq(ps[i].x - mid_x) < d) {
            stripe.push_back(ps[i]);
        }
    }

    sort(stripe.begin(), stripe.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });

    for (int i = 0; i < (int) stripe.size(); i++) {
        for (int j = i + 1; j < (int) stripe.size(); j++) {
            if (sq(stripe[j].y - stripe[i].y) >= d) {
                break;
            }
            d = min(d, distance(stripe[i], stripe[j]));
        }
    }

    return d;
}

int main() {
    int n;
    cin >> n;
    vector<Point> ps(n);
    for (int i = 0; i < n; i++) {
        cin >> ps[i].x >> ps[i].y;
    }
    sort(ps.begin(), ps.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    cout << min_distance(ps, 0, n) << "\n";
    return 0;
}
