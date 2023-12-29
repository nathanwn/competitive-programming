#include <iostream>

using namespace std;

bool is_balance(const string& t) {
    if (t.size() % 2 != 0) {
        return false;
    }

    int count_a = 0;
    for (char c : t) {
        if (c == 'a') {
            count_a++;
        }
    }
    return (int) t.size() == count_a * 2;
}

struct Solution {
    void solve() {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                string t = s.substr(i, j - i + 1);
                if (is_balance(t)) {
                    cout << i + 1 << " " << j + 1 << '\n';
                    return;
                }
            }
        }
        cout << -1 << " " << -1 << '\n';
    }
};

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        Solution s;
        s.solve();
    }
    return 0;
}
