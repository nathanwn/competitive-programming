#pragma once

#include <stdint.h>

template <typename T, int md>
struct Modnum {
    T v;
    Modnum(T _v=0) : v(normalize(_v)) {}

    T normalize(int64_t x) {
        if (x < -md || x >= md) x %= md;
        if (x < 0) x += md;
        return x;
    }

    Modnum operator+(Modnum o) {
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

    ModNum pow(int64_t x) {
        ModNum a = v;
        ModNum res = 1;
        while (x > 0) {
            if (x & 1) res *= a;
            a *= a;
            x >>= 1;
        }
        return res;
    }

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

