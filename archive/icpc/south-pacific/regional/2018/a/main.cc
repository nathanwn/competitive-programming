#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l;
    cin >> n >> l;
    vector<string> s(n);

    int len = 0;

    for (int i = 0; i < n; i++) {
        cin >> s[i];
        len += s[i].length();
    }

    if (n == 1) {
        cout << ((l == len) ? "Yes" : "No") << '\n';
        return 0;
    }

    int gaps = n - 1;
    int remaining = l - len;

    if (remaining <= 0) {
        cout << "No\n";
        return 0;
    }

    cout << ((remaining % gaps == 0) ? "Yes" : "No") << '\n';

    return 0;
}
