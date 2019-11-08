// 問從 src 到 dst 的最小 edit distance
// ins 插入一個字元的成本
// del 刪除一個字元的成本
// sst 替換一個字元的成本
ll edd(string& src, string& dst, ll ins, ll del, ll sst) {
    ll dp[src.size() + 1][dst.size() + 1]; // 不用初始化
    for (int i = 0; i <= src.size(); i++) {
        for (int j = 0; j <= dst.size(); j++) {
            if (i == 0) dp[i][j] = ins * j;
            else if (j == 0) dp[i][j] = del * i;
            else if (src[i - 1] == dst[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min(dp[i][j - 1] + ins,
                            min(dp[i - 1][j] + del,
                             dp[i - 1][j - 1] + sst));
        }
    }
    return dp[src.size()][dst.size()];
}
