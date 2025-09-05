#pragma once

#include <vector>
#include <string>

using namespace std;

vector<int> kmp(string& s) {
    int n = (int)s.length();
    vector<int> f(n);
    for (int i = 1; i < n; i++) {
        int j = f[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = f[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        f[i] = j;
    }
    return f;
}
