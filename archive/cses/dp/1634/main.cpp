#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void minimize(T& a, T b) { a = min(a, b); }

template <typename T>
void maximize(T& a, T b) { a = max(a, b); }

const int inf = 1e9;

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    // dp[x]: minimum number of coins to reach target `x`
    vector<int> dp(target + 1, inf);
    dp[0] = 0;
    for (int x = 1; x <= target; x++) {
        for (int i = 0; i < n; i++) {
            if (x - c[i] >= 0) {
                minimize(dp[x], dp[x - c[i]] + 1);
            }
        }
    }
    cout << (dp[target] == inf ? -1 : dp[target]) << "\n";
    return 0;
}
