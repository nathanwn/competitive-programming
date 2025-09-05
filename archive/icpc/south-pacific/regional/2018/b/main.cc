#include <bits/stdc++.h>

using namespace std;

vector<int> zFunction(const string& s) {
    int n = s.length();
    vector<int> z(n);

    int l = 0;
    int r = 0;

    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

string construct(const string& s, int start) {
    string t;
    for (int i = start; i < (int) s.length(); i += 2) {
        t += s[i];
    }
    t += '\0';
    t += s;
    return t;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.length();

    string t0 = construct(s, 0);
    string t1 = construct(s, 1);

    vector<int> z0 = zFunction(t0);
    vector<int> z1 = zFunction(t1);

    int t0_zmax = 1;
    int t1_zmax = 1;

    for (int i = 0; i < n; i++) {
        t0_zmax = max(t0_zmax, z0[t0.length() - s.length() - 1 + i]);
        t1_zmax = max(t1_zmax, z1[t1.length() - s.length() - 1 + i]);
    }

    int t0_ans = min(n, t0_zmax * 2);
    int t1_ans = min(n, t1_zmax * 2 + 1);

    int ans = max(t0_ans, t1_ans);
    cout << ans << '\n';

    return 0;
}
