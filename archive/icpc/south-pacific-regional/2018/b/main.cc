#include <bits/stdc++.h>

using namespace std;

/**
 * Idea: Let p[i] be the ith character on the plate
 *
 *   Assume that p[i] is indeed the first character in p that forms the
 * longest prefix for s, then either:
 * - Case 1:
 *   p[i]     = s[0]
 *   p[i + 1] = s[2]
 *   p[i + 2] = s[4]
 *   ...
 *   p[i + k] = s[2k]
 * - Case 2:
 *   p[i]     = s[1]
 *   p[i + 1] = s[3]
 *   p[i + 2] = s[5]
 *   ...
 *   p[i + k] = s[2k + 1]
 *
 *   Let p[i..i + k - 1] (k characters) be the part of p that forms the longest
 * prefix for s.
 *   If case 1 occurs, then the longest prefix that can be form for s would have
 * length (k * 2).
 *   If case 2 occurs, then the longest prefix that can be form for s would have
 * length (k * 2 + 1).
 *   Caution: in both case, the length of the longest prefix cannot exceed
 * the length of s itself!
 *
 *   How to find p[i..i + k - 1]?
 *   Step 1: Construct a new string t for both cases:
 * - Case 1: t = s[0, 2, 4, ..] + '\0' + s
 * - Case 2: t = s[1, 3, 5, ..] + '\0' + s
 *
 *   Step 2: Run Z-algorithm on t for both cases
 *
 *   Step 3: For each case, the maximum z value in the "later part" of t (after
 *   the '\0' character) would be the value k that we are trying to find.
**/

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

    for (int i = 0; i < n; i++) {
    }

    int t0_ans = min(n, t0_zmax * 2);
    int t1_ans = min(n, t1_zmax * 2 + 1);

    int ans = max(t0_ans, t1_ans);
    cout << ans << '\n';

    return 0;
}
