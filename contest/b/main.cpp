#include <bits/stdc++.h>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

int main() {
    string s;
    cin >> s;
    queue<char> q;
    for (char c : s) q.push(c);
    string t;
    if (s[0] == 'o') t.push_back('i');
    while (!q.empty()) {
        char c = q.front(); q.pop();
        if (c == t.back()) {
            if (c == 'i') t.push_back('o');
            else t.push_back('i');
        }
        t.push_back(c);
    }
    int ans = t.size() - s.size();
    if (t.size() % 2 != 0) ans++;
    std::cout << ans << "\n";
    return 0;
}
