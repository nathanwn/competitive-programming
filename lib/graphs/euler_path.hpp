/// Hierholzer's Algorithm

vector<int> findDirectedEulerPath(vector<vector<int>>& adj, int s) {
    int n = adj.size();

    vector<int> edge_id(n, 0);
    stack<int> st;
    vector<int> res;

    st.push(s);

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        while (edge_id[u] < (int) adj[u].size()) {
            st.push(u);
            u = adj[u][edge_id[u]++];
        }

        res.push_back(u);
    }

    reverse(res.begin(), res.end());
    return res;
}
