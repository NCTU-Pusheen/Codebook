int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int a[LEN],b[LEN];
    for(int i=1; i<=n; i++) scanf("%d", &a[i]);
    for(int i=1; i<=m; i++) scanf("%d", &b[i]);
    int dp[LEN][LEN] = {};  // dp[i][j]:以b[j]結尾的LCIS長度
    int pre[LEN][LEN] = {};  // 用來回溯
    for(int i=1; i<=n; i++) {
        int p = 0;
        for(int j=1; j<=m; j++) {
            if(a[i]!=b[j]) {
                dp[i][j] = dp[i-1][j];
                pre[i][j] = j;
                if( a[i]>b[j] && dp[i-1][j]>dp[i-1][p] )
                    p = j;
            } else {
                dp[i][j] = dp[i-1][p]+1;
                pre[i][j] = p;
            }
        }
    }
    int len = 0, p = 0;
    for(int j=1; j<=m; j++) {
        if(dp[n][j]>len) {
            len = dp[n][j];
            p = j;
        }
    }
    printf("LEN = %d\n", len);
    vector<int> ans;
    for(int i=n; i>=1; i--) {
        if(a[i]==b[p])
            ans.push_back(b[p]);
        p = pre[i][p];
    }
    while(ans.size()) {
        printf("%d ",ans.back());
        ans.pop_back();
    }
    return 0;
}
