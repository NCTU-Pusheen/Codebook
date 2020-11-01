// Time: O(VE)
const int INF = 2e9;
const int N = ? ;       // 男女總人數；女 id: 0 ~ p，男 id: p+1 ~ N-1
int vis[N], rnd, m[N];  // 跑完匈牙利後配對結果儲存於此， -1 表示人醜
vector<int> g[N];       // 關係表
int dfs(int s) {
    for (int x : g[s]) {
        if (vis[x]) continue;
        vis[x] = 1;
        if (m[x] == -1 || dfs(m[x])) {
            m[x] = s, m[s] = x;
            return 1;
        }
    } return 0;
}
int hungarian(int p) {  // p : 女性人數
    memset(m, -1, sizeof(m));
    int c = 0;
    for (int i = 0; i < p; i++) {
        if (m[i] == -1) {
            memset(vis, 0, sizeof(vis));
            c += dfs(i);
        }
    } return c; // 成功結婚對數
}
