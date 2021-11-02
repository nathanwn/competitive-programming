#include <bits/stdc++.h>

using namespace std;

struct Trie {
    const int ALPHA = 26;
    vector<vector<int>> trie;
    vector<int> count;

    int ord(char c) { return c - 'a'; }

    Trie() {
        trie.emplace_back(ALPHA, -1);
        count.push_back(0);
    }

    void add(const string& word) {
        int node = 0;

        for (char c : word) {
            int x = ord(c);

            if (trie[node][x] == -1) {
                trie[node][x] = trie.size();
                trie.emplace_back(ALPHA, -1);
                count.push_back(0);
            }

            node = trie[node][x];
            count[node]++;
        }
    }

    int shortestUniquePrefix(const string& word) {
        int node = 0;

        for (int i = 0; i < (int) word.length(); i++) {
            char c = word[i];
            int x = ord(c);
            node = trie[node][x];
            if (count[node] == 1) {
                return i + 1;
            }
        }

        return word.length();
    }
};

struct Solver {
    int n;
    vector<string> words;

    Solver() {
        cin >> n;
        words.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> words[i];
        }
    }

    int solve() {
        int ans = 0;

        Trie trie;

        for (const string& word : words) {
            trie.add(word);
            ans += trie.shortestUniquePrefix(word);
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        Solver solver;
        cout << "Case #" << ti << ": " << solver.solve() << '\n';
    }

    return 0;
}
