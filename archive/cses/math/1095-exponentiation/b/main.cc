#include <bits/stdc++.h>

using namespace std;

template <typename T, int md>
struct Modnum {
    T v;
    Modnum() : v(0) {}
    Modnum(T _v) : v(normalize(_v)) {}

    T normalize(int64_t x) {
        if (x < -md || x >= md) x %= md;
        if (x < 0) x += md;
        return x;
    }

    Modnum& operator+=(const Modnum& o) {
        if ((v += o.v) >= md) v -= md;
        return *this;
    }

    Modnum& operator-=(const Modnum& o) {
        if ((v -= o.v) < 0) v += md;
        return *this;
    }

    Modnum& operator*=(const Modnum& o) {
        int64_t r = (int64_t) v * o.v;
        r %= md;
        v = r;
        return *this;
    }

    Modnum operator+(const Modnum& o) const { return Modnum(v) += o; }
    Modnum operator-(const Modnum& o) const { return Modnum(v) -= o; }
    Modnum operator*(const Modnum& o) const { return Modnum(v) *= o; }

    Modnum pow(int64_t x) {
        Modnum a = v;
        Modnum res = 1;
        while (x > 0) {
            if (x & 1) res *= a;
            a *= a;
            x >>= 1;
        }
        return res;
    }

    friend istream& operator>>(istream& is, Modnum& obj) {
        return is >> obj.v;
    }

    friend ostream& operator<<(ostream& os, const Modnum& obj) {
        return os << obj.v;
    }
};

const int MOD = 1e9 + 7;
using ModInt = Modnum<int, MOD>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        ModInt a;
        int b;
        cin >> a >> b;
        cout << a.pow(b) << '\n';
    }

    return 0;
}
