struct SparseTable {
    vector<vector<int or ll>> a;
    // Constructs a sparse table.
    SparseTable(vector<int or ll>& data) {
        int n = data.size();
        a.assign(floor(log2(n)) + 1, vector<int or ll>(n));
        a[0] = data;
        for (int i = 1; (1 << i) <= n; i++) {
            int k = n - (1 << i);
            for (int j = 0; j <= k; j++) {
                a[i][j] = max(a[i - 1][j], a[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    // Queries the maximum element in [l, r] where 0- or 1-based are both safe.
    ll maximal(int l, int r) {
        int k = floor(log2(r - l + 1));
        return max(a[k][l], a[k][r - (1 << k) + 1]);
    }
};
