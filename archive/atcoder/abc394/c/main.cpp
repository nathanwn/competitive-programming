#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.length();

    vector<pair<int, int>> segments;

    for (int l = 0; l < n; ) {
        if (s[l] != 'W') {
            l++;
            continue;
        }

        int r = l + 1;
        while (r < n && s[r] == 'W') r++;

        if (r < n && s[r] == 'A') {
            segments.emplace_back(l, r);
            l = r + 1;
        } else {
            l = r;
        }
    }

    for (auto& [l, r] : segments) {
        s[l] = 'A';
        for (int i = l + 1; i <= r; i++) s[i] = 'C';
    }

    cout << s << endl;

    return 0;
}
