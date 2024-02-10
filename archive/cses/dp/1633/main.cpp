#include <iostream>
#include <vector>

using namespace std;

const int MOD = int(1e9) + 7;
const int N = int(1e6);

void add(int& a, int b) {
    a += b;
    if (a >= MOD) a-= MOD;
}

int main() {
    int n;
    cin >> n;
    vector<int> dp(N + 7, 0);
    dp[0] = 1;
    for (int i = 0; i <= N; i++) {
        for (int j = 1; j <= 6; j++) {
            add(dp[i + j], dp[i]);
        }
    }
    cout << dp[n] << "\n";
    return 0;
}
