/// Warning: not tested!

struct KMP {
    string s;
    vector<int> fn;

    KMP(string& s) : s(s) {
        int lenS = s.length();
        fn.assign(lenS, 0);

        for (int i = 1; i < lenS; i++) {
            int j = fn[i - 1];

            while (j > 0 && s[i] != s[j]) {
                j = fn[j - 1];
            }

            if (s[i] == s[j]) {
                j++;
            }

            fn[i] = j;
        }
    }

    vector<int> match(const string& t, int lenS) {
        vector<int> matches;
        int lenT = t.length();
        int j = 0;

        for (int i = 0; i < lenT; i++) {
            while (j > 0 && s[j] != t[i]) {
                j = fn[j - 1];
            }

            if (s[j] == t[i]) {
                j++;
            }

            if (j == lenS) {
                matches.push_back(i - j + 1);
                j = fn[j - 1];
            }
        }

        return matches;
    }
};

#endif // KMP_H_
