#include <bits/stdc++.h>

using namespace std;

struct Solver {
    int n, nq;
    vector<int> a;
    vector<int> q;
    vector<int64_t> pre_sum;
    set<int64_t> vals;

    void calcPresum() {
        pre_sum[0] = a[0];

        for (int i = 1; i < n; i++) {
            pre_sum[i] = pre_sum[i - 1] + a[i];
        }
    }

    int64_t getSum(int from, int to) {
        if (from == 0) return pre_sum[to];
        else return pre_sum[to] - pre_sum[from - 1];
    }

    void slice(int from, int to) {
        if (from > to) return;

        vals.insert(getSum(from, to));

        if (from == to || a[from] == a[to]) return;

        int avg = (a[from] + a[to]) / 2;
        int pivot = -1;

        int left = from;
        int right = to;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (a[mid] <= avg) {
                pivot = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        assert(pivot != -1);

        slice(from, pivot);
        slice(pivot + 1, to);
    }

    Solver() {
        cin >> n >> nq;
        a.resize(n);
        pre_sum.resize(n);
        q.resize(nq);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }


        for (int i = 0; i < nq; i++) {
            cin >> q[i];
        }

        sort(a.begin(), a.end());
        calcPresum();
        slice(0, n - 1);

        for (int i = 0; i < nq; i++) {
            if (vals.find(q[i]) != vals.end()) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        Solver solver;
    }

    return 0;
}
