/*
時間複雜度 O(VE)
*/
const int INF = 2e9;
const int N = ? ;       // 男女總人數；女性 index 0 ~ p ，男性 index p+1 ~ N-1
int vis[N], rnd, m[N];  // 跑完匈牙利之後配對結果儲存於此， -1 表示人醜
vector<int> g[N];       // 關係表

int dfs(int s) {
    for (int x : g[s]) {
        if (vis[x]) continue;
        vis[x] = 1;
        if (m[x] == -1 || dfs(m[x])) {
            m[x] = s, m[s] = x;
            return 1;
        }
    }
    return 0;
}

// 回傳成功結婚對數
int hungarian(int p) {  // 傳入女性人數
    memset(m, -1, sizeof(m));
    int c = 0;
    for (int i = 0; i < p; i++) {
        if (m[i] == -1) {
            memset(vis, 0, sizeof(vis));
            c += dfs(i);
        }
    }
    return c;
}
