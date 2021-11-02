#include <bitset>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

int is_left_bracket(char c) {
    return c == '(' ||
           c == '[' ||
           c == '<';
}

int are_pair(char l, char r) {
    return (l == '(' && r == ')') ||
           (l == '[' && r == ']') ||
           (l == '<' && r == '>');
}

bool solve() {
    string s;
    cin >> s;

    vector<char> st;
    for (char c : s) {
        if (!is_left_bracket(c)) {
            if ((int) st.size() == 0) return false;
            if (!are_pair(st.back(), c)) {
                return false;
            }
            st.pop_back();
        } else {
            st.push_back(c);
        }
    }
    return (int) st.size() == 0;
}

int main() {
    cout << (solve() ? "Yes" : "No") << endl;
    return 0;
}
