#include <bitset>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

std::string _repr_(const std::string &s) { return '"' + s + '"'; }
std::string _repr_(const char *s) { return _repr_((std::string)s); }
std::string _repr_(bool b) { return (b ? "true" : "false"); }
std::string _repr_(int32_t x) { return std::to_string(x); }
std::string _repr_(int64_t x) { return std::to_string(x); }
std::string _repr_(uint32_t x) { return std::to_string(x); }
std::string _repr_(uint64_t x) { return std::to_string(x); }
std::string _repr_(double x) { return std::to_string(x); }
std::string _repr_(long double x) { return std::to_string(x); }

template <typename A, typename B>
std::string _repr_(std::pair<A, B> p);

template <typename A, typename B>
std::string _repr_(std::tuple<A, B> p);

template <typename A, typename B, typename C>
std::string _repr_(std::tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
std::string _repr_(std::tuple<A, B, C, D> p);

template <size_t N>
std::string _repr_(std::bitset<N> v) {
    std::string res;
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
std::string _repr_(A v) {
    bool first = true;
    std::string res = "{";
    for (auto &&x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += _repr_(x);
    }
    res += "}";
    return res;
}

template <typename A, typename B>
std::string _repr_(std::pair<A, B> p) {
    return "(" + _repr_(p.first) + ", " + _repr_(p.second) + ")";
}

template <typename A, typename B>
std::string _repr_(std::tuple<A, B> p) {
    return "(" + _repr_(std::get<0>(p)) + ", " + _repr_(std::get<1>(p)) + ")";
}

template <typename A, typename B, typename C>
std::string _repr_(std::tuple<A, B, C> p) {
    return "(" + _repr_(std::get<0>(p)) + ", " + _repr_(std::get<1>(p)) + ", " +
           _repr_(std::get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
std::string _repr_(std::tuple<A, B, C, D> p) {
    return "(" + _repr_(std::get<0>(p)) + ", " + _repr_(std::get<1>(p)) + ", " +
           _repr_(std::get<2>(p)) + ", " + _repr_(std::get<3>(p)) + ")";
}

void debug_out() { std::cerr << std::endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    std::cerr << " " << _repr_(H);
    debug_out(T...);
}

#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
