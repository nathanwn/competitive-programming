#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

// map<tuple<int, int, int>, int> mem;
unordered_map<tuple<int, int, int>, int> mem;
vector<int> a;
vector<int> b;


int max_defeat(int i, int h, int m) {
    if (i == 0) return 0;
    auto key = make_tuple(i, h, m);
    auto it = mem.find(key);
    if (it != mem.end()) {
        return it->second;
    }
    int res = max_defeat(i - 1, h, m);
    if (h >= a[i - 1]) res = max(res, max_defeat(i - 1, h - a[i - 1], m) + 1);
    if (m >= b[i - 1]) res = max(res, max_defeat(i - 1, h, m - b[i - 1]) + 1);
    mem[key] = res;
    return res;
}

int main() {
    int n, h, m;
    cin >> n >> h >> m;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
/**
    max_defeat(0, i, h, m) =
        max(
            max_defeat(0, i - 1, h - a[i], m       ),
            max_defeat(0, i - 1, h       , m - b[i]),
        )
**/
    cout << max_defeat(n, h, m) << "\n";
    return 0;
}
