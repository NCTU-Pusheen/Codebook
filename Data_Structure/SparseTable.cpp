#define flg(a) floor(log2(a))
struct SparseTable {
    vector<vector<ll>> a;
    SparseTable(vector<ll>& data) {
        int n = data.size();
        a.assign(flg(n) + 1, vector<ll>(n));
        a[0] = data;
        for (int i = 1; (1 << i) <= n; i++)
            for (int j = 0, k = n - (1 << i); j <= k; j++)
                a[i][j] = max(a[i - 1][j],
                              a[i - 1][j + (1 << (i - 1))]);
    }
    ll maxx(int l, int r) { // [l, r], 0/1-based
        int k = flg(r - l + 1);
        return max(a[k][l], a[k][r - (1 << k) + 1]);
    }
};
