#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    double p_switch;

    cin >> n >> p_switch;

    double p_happy = 1;

    while (n) {
        if (n & 1) {
            p_happy   = p_happy * (1 - p_switch) + (1 - p_happy) * p_switch;
        }

        p_switch = p_switch * (1 - p_switch) + (1 - p_switch) * p_switch;
        n >>= 1;
    }

    cout << p_happy << '\n';

    return 0;
}
