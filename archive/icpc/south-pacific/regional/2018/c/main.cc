#include <bits/stdc++.h>

using namespace std;

struct Star {
    int t;
    int d;
};

bool cmp_d(Star& s1, Star& s2) {
    return s1.d < s2.d;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<Star> stars;

    for (int i = 0; i < n; i++) {
        int t, d;
        cin >> t >> d;
        stars.push_back({t, d});
    }

    sort(stars.begin(), stars.end(),
        [](const Star& s1, const Star& s2) {
            return s1.d < s2.d;
        });

    int j = 0;
    map<int, int> at_time; // key = time, value = count

    int64_t ans = 0;

    for (int i = 0; i < k; i++) {
        int already = i;

        while (j < n && stars[j].d <= already) {
            if (at_time.find(stars[j].t) == at_time.end()) {
                at_time.insert(make_pair(stars[j].t, 1));
            } else {
                at_time[stars[j].t]++;
            }
            j++;
        }

        if (at_time.size() == 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }

        ans += at_time.begin()->first;
        at_time.begin()->second--;
        if (at_time.begin()->second == 0) at_time.erase(at_time.begin());
    }

    cout << ans << '\n';

    return 0;
}
