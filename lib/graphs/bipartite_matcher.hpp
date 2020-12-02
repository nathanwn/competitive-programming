/// Wrote a long long time ago (90% sure it is correct)
/// Still need to test some day soon

#ifndef HOPCROFT_KARP_H_
#define HOPCROFT_KARP_H_

struct HopcroftKarp {
    const int INF = (int) 1e9;
    int nU;
    int nV;
    vector<vector<int>> adj;
    vector<int> layer;
    vector<int> mateOfU;
    vector<int> mateOfV;

    Matcher(int nU, int nV) : nU(nU), nV(nV) {
        adj.resize(nU);
        layer.resize(nU);
        mateOfU.resize(nU, -1);
        mateOfV.resize(nV, -1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        // Find all possible augmenting paths
        queue<int> q;

        for (int u = 0; u < nU; u++) {
            // Consider only unmatched edges
            if (mateOfU[u] == -1) {
                layer[u] = 0;
                q.push(u);
            }
            else {
                layer[u] = INF;
            }
        }

        bool hasAugPath = false;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int& v : adj[u]) {
                if (mateOfV[v] == -1) {
                    hasAugPath = true;
                }
                else if (layer[mateOfV[v]] == INF) {
                    layer[mateOfV[v]] = layer[u] + 1;
                    q.push(mateOfV[v]);
                }
            }
        }

        return hasAugPath;
    }

    bool dfs(int u) {
        if (layer[u] == INF) {
            return false;
        }

        for (int v : adj[u]) {
            if ((mateOfV[v] == -1) || (layer[mateOfV[v]] == layer[u] + 1 && dfs(mateOfV[v]))) {
                mateOfV[v] = u;
                mateOfU[u] = v;
                return true;
            }
        }

        return false;
    }

    int maxMatching() {
        int matching = 0;

        while (bfs()) { // there is at least 1 augmenting path
            for (int u = 0; u < nU; u++) {
                if (mateOfU[u] == -1 && dfs(u)) {
                    ++matching;
                }
            }
        }

        return matching;
    }
};

#endif // HOPCROFT_KARP_H_
