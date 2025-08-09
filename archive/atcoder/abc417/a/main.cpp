#include <iostream>
#include <vector>
#include <string>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

struct Solver {
    Solver(istream& in, ostream& out) {
        int n, a, b;
        in >> n >> a >> b;
        string s;
        in >> s;
        out << s.substr(a, n - a - b) << "\n";
    }
};

int main() {
    Solver solver(cin, cout);
    return 0;
}
