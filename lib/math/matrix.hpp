#pragma once

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
};

template <class T, int md>
istream& operator>>(istream& is, const Modnum<T, md>& obj) {
    is >> obj.v;
    return is;
}

template <class T, int md>
ostream& operator<<(ostream& os, const Modnum<T, md>& obj) {
    os << obj.v;
    return os;
}

const int MOD = 1e9 + 7;
using ModInt = Modnum<int, MOD>;
using ModInt64 = Modnum<int64_t, MOD>;

