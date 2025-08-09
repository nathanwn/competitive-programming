#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    int c = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    for (int j = 0; j < q; j++) {
        int t;
        cin >> t;
        if (t == 1) {
            int p, x;
            cin >> p >> x;
            p -= 1;
            p += c;
            p %= n;
            a[p] = x;
        } else if (t == 2) {
            int p;
            cin >> p;
            p -= 1;
            p += c;
            p %= n;
            cout << a[p] << "\n";
        } else {
            int k;
            cin >> k;
            c += k;
            c %= n;
        }
    }
    return 0;
}
