#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>

using namespace std;

struct Element {
    int val;
    int id;
    int order;
    int seg;

    static bool val_cmp(const Element &e1, const Element &e2) {
      return e1.val < e2.val;
    }

    static bool id_cmp(const Element &e1, const Element &e2) {
      return e1.id < e2.id;
    }
};

struct Solution {
    int n;
    vector<Element> a;
    vector<vector<int> > ans;

    Solution() {
        cin >> n;
        a.resize(n);

        for (int i = 0; i < n; i++) {
            a[i].id = i;
            cin >> a[i].val;
        }

        sort(a.begin(), a.end(), Element::val_cmp);
        for (int i = 0; i < n; i++) {
            a[i].order = i;
        }
        sort(a.begin(), a.end(), Element::id_cmp);

        while (true) {
            a[n - 1].seg = 1;

            for (int i = n - 2; i > -1; i--) {
                if (a[i].order + 1 == a[i + 1].order) {
                    a[i].seg = a[i + 1].seg + 1;
                } else {
                    a[i].seg = 1;
                }
            }

            bool found = false;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (a[i].order - 1 == a[j].order) {
                        found = true;
                        shiftLeft(i, j, a[i].seg);
                        break;
                    }
                }
                if (found) break;
            }
            if (!found) break;
        }

        cout << ans.size() << '\n';
        for (int i = 0; i < (int) ans.size(); i++) {
            cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << '\n';
        }
    }

    void shiftLeft(int l, int r, int d) {
        vector<int> move(3);
        move[0] = l + 1; move[1] = r + 1; move[2] = d;
        ans.push_back(move);

        vector<Element> b = a; // b is a copy of a
        assert(l < r);
        assert(0 <= l && r < n);
        for (int i = l; i <= r; i++) {
            int j = i - d;
            if (j < l) {
                j += r - l + 1;
            }
            assert(l <= j && j <= r);
            b[j] = a[i];
        }
        swap(a, b);
    }
};

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        Solution();
    }
    return 0;
}
