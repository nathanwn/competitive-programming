/// Tested: FHC 2015 Round 1 B

#pragma once

struct Trie {
    const int ALPHA = 26;
    vector<vector<int>> trie;
    vector<int> eow;

    int ord(char c) { return c - 'a'; }

    Trie() {
        trie.emplace_back(ALPHA, -1);
        eow.push_back(0);
    }

    void add(const string& word) {
        int node = 0;

        for (char c : word) {
            int x = ord(c);

            if (trie[node][x] == -1) {
                trie[node][x] = trie.size();
                trie.emplace_back(ALPHA, -1);
                eow.push_back(0);
            }

            node = trie[node][x];
            eow[node]++;
        }
    }
};
