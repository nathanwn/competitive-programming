// Solution by Matt

#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n; long long k;
    string s;
    cin >> n >> k;
    string sub[4];
    long long size = n/4;
    cin >> s;
    for (int i = 0; i < 4; i++) {
        sub[i] = s.substr(i * size, size);
    }
    cout << sub[0];
    switch (k%3) {
        case 0:
            cout << sub[1];
            cout << sub[2];
            cout << sub[3];
            break;
        case 1:
            cout << sub[3];
            cout << sub[1];
            cout << sub[2];
            break;
        case 2:
            cout << sub[2];
            cout << sub[3];
            cout << sub[1];
            break;
        default:
            break;
    }
}
