#include <bits/stdc++.h>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    unordered_set<int> pre;
    vector<int> pre_cnt(n, 0);
    unordered_set<int> suf;
    vector<int> suf_cnt(n, 0);
    for (int i = 0; i < n; i++) {
        pre.insert(a[i]);
        pre_cnt[i] = pre.size();
    }
    for (int i = n - 1; i > -1; i--) {
        suf.insert(a[i]);
        suf_cnt[i] = suf.size();
    }
    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans = max(ans, pre_cnt[i] + suf_cnt[i + 1]);
    }
    cout << ans << "\n";
    return 0;
}
