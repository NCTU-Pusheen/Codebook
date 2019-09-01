int edit_distance(string s, string t) {
    int n = s.size(), m = t.size();
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) dp[i][0] = i;
    for (int i = 1; i <= m; i++) dp[0][i] = i;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = min(dp[i -1][j - 1] + !(s[i - 1] == t[j - 1]), min(dp[i][j - 1], dp[i - 1][j]) + 1);
    return dp[n][m];
}
