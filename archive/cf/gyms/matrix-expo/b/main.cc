#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct vec2d : public vector<vector<T>> {
    vec2d(int n=0, int m=0, T t=T())
        : vector<vector<T>>(n, vector<T>(m, t)) {}
};

template <typename T>
struct Matrix : vec2d<T> {
    int n;

    Matrix(int n_, T t=T()) : vec2d<T>(n_, n_, t), n(n_) {}

    Matrix operator+(const Matrix& o) const {
        assert(n == o.n);
        const Matrix& a = *this;
        Matrix res(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = a[i][j] + o[i][j];
            }
        }

        return res;
    }

    Matrix operator-(const Matrix& o) const {
        assert(n == o.n);
        const Matrix& a = *this;
        Matrix res(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = a[i][j] - o[i][j];
            }
        }

        return res;
    }

    Matrix operator*(const Matrix& o) const {
        assert(n == o.n);
        const Matrix& a = *this;
        Matrix res(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    res[i][j] += a[i][k] * o[k][j];
                }
            }
        }
        return res;
    }

    void identity() {
        Matrix& a = *this;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) a[i][j] = 1;
                else a[i][j] = 0;
            }
        }
    }
};

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
        v *= o.v; v %= md; return *this;
    }

    Modnum operator+(const Modnum& o) const { return Modnum(v) += o; }
    Modnum operator-(const Modnum& o) const { return Modnum(v) -= o; }
    Modnum operator*(const Modnum& o) const { return Modnum(v) *= o; }

    friend istream& operator>>(istream& is, const Modnum& obj) {
        return is >> obj.v;
    }

    friend ostream& operator<<(ostream& os, const Modnum& obj) {
        return os << obj.v;
    }
};

const int MOD = 1e9 + 7;
using ModInt = Modnum<int, MOD>;
using ModInt64 = Modnum<int64_t, MOD>;

int main() {
    int64_t n;
    cin >> n;

    Matrix<ModInt64> m(2);
    m[0][0] = 19;
    m[0][1] = 7;
    m[1][0] = 6;
    m[1][1] = 20;

    Matrix<ModInt64> res(2);
    res.identity();

    while (n) {
        if (n & 1) {
            res = res * m;
        }
        m = m * m;
        n >>= 1;
    }

    cout << res[0][0] << '\n';

    return 0;
}
