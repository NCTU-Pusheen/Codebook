/** Queires minimal distance to fix string src to dst. */
ll ins = ? ;  // cost of insertion
ll del = ? ;  // cost of deletion
ll sst = ? ;  // cost of substitution
ll edd(string& src, string& dst) {
    ll dp[src.size() + 1][dst.size() + 1];
    for (int i = 0; i <= src.size(); i++) {
        for (int j = 0; j <= dst.size(); j++) {
            if (i == 0)
                dp[i][j] = ins * j;
            else if (j == 0)
                dp[i][j] = del * i;
            else if (src[i - 1] == dst[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else {
                dp[i][j] = min(dp[i][j - 1] + ins,
                               min(dp[i - 1][j] + del,
                                   dp[i - 1][j - 1] + sst));
            }
        }
    }
    return dp[src.size()][dst.size()];
}
