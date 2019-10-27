/** 適用於初始化後不修改的情況，只能查極值。 **/
#define cc(a) floor(log2(a)) // 加速
struct SparseTable {
    // 不會 overflow 的話可以情況全部換成 vector<int>
    vector<vector<ll>> a;
    // 建立空的 sparse table ，元素初始為 data 。不可更改。
    SparseTable(vector<ll>& data) {
        int n = data.size();
        a.assign(cc(n) + 1, vector<ll>(n));
        a[0] = data;
        for (int i = 1; (1 << i) <= n; i++) {
            int k = n - (1 << i);
            for (int j = 0; j <= k; j++) {
                a[i][j] = max(a[i - 1][j],
                            a[i - 1][j + (1 << (i - 1))]);
    }}}
    // 查詢 [l, r] 區間最大值。0/1-based 都安全。
    ll maxx(int l, int r) {
        int k = cc(r - l + 1);
        return max(a[k][l], a[k][r - (1 << k) + 1]);
    }
};
