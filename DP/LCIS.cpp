vector<int> LCIS(vector<int> a, vector<int> b) {
    int n = a.size(), m = b.size();
    int dp[LEN][LEN] = {}, pre[LEN][LEN] = {};
    for(int i=1; i<=n; i++) {
        int p = 0;
        for(int j=1; j<=m; j++)
            if(a[i-1]!=b[j-1]) {
                dp[i][j] = dp[i-1][j], pre[i][j] = j;
                if( a[i-1]>b[j-1] && dp[i-1][j]>dp[i-1][p] )
                    p = j;
            } else {
                dp[i][j] = dp[i-1][p]+1, pre[i][j] = p;
            }
    }
    int len = 0, p = 0;
    for(int j=1; j<=m; j++)
        if(dp[n][j]>len) len = dp[n][j], p = j;
    vector<int> ans;
    for(int i=n; i>=1; i--) {
        if(a[i-1]==b[p-1]) ans.push_back(b[p-1]);
        p = pre[i][p];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}