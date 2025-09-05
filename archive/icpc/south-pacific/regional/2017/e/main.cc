// Solution by Yash

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    // Iterate over increments (which range from 1 to (n-1)/2)
    for (int i = 1; i <= (n-1)/2; i++) {
        int start = 1;
        int end;
        for (int j = 0; j < n; j++) {
            end = (start + i)%n;
            if (end == 0) {
                end = n;
            }
            cout << start << " " << end << endl;
            start = end;
        }
    }

}
