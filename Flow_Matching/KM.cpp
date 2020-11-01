/* 時間複雜度 O(N^3)
求完美匹配中的最大權匹配
如果不存在完美匹配，求最大匹配
如果存在數個最大匹配，求數個最大匹配當中最大權匹配 */
const ll INF = 5e18;
const int N = ?;  // maxn
int n;            // count of vertex (one side)
ll g[N][N];       // weights
class KM {
   private:
    ll lx[N], ly[N], s[N];
    int px[N], py[N], m[N], p[N];
    void adj(int y) {  // 把增廣路上所有邊反轉
        m[y] = py[y];
        if (px[m[y]] != -2)
            adj(px[m[y]]);
    }
    bool dfs(int x) {  // DFS找增廣路
        for (int y = 0; y < n; ++y) {
            if (py[y] != -1) continue;
            ll t = lx[x] + ly[y] - g[x][y];
            if (t == 0) {
                py[y] = x;
                if (m[y] == -1) {
                    adj(y);
                    return 1;
                }
                if (px[m[y]] != -1) continue;
                px[m[y]] = y;
                if (dfs(m[y])) return 1;
            } else if (s[y] > t) {
                s[y] = t, p[y] = x;
            }
        }
        return 0;
    }

   public:
    ll max_weight() {
        memset(ly, 0, sizeof(ly));
        memset(m, -1, sizeof(m));
        for (int x = 0; x < n; ++x) {
            lx[x] = -INF;
            for (int y = 0; y < n; ++y)
                lx[x] = max(lx[x], g[x][y]);
        }
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) s[y] = INF;
            memset(px, -1, sizeof(px));
            memset(py, -1, sizeof(py));
            px[x] = -2;
            if (dfs(x)) continue;
            bool flag = 1;
            while (flag) {
                ll cut = INF;
                for (int y = 0; y < n; ++y)
                    if (py[y] == -1 && cut > s[y]) cut = s[y];
                for (int j = 0; j < n; ++j) {
                    if (px[j] != -1) lx[j] -= cut;
                    if (py[j] != -1) ly[j] += cut;
                    else s[j] -= cut;
                }
                for (int y = 0; y < n; ++y) {
                    if (py[y] == -1 && s[y] == 0) {
                        py[y] = p[y];
                        if (m[y] == -1) {
                            adj(y);
                            flag = 0;
                            break;
                        }
                        px[m[y]] = y;
                        if (dfs(m[y])) {
                            flag = 0;
                            break;
                        }
                    }
                }
            }
        }
        ll ans = 0;
        for (int y = 0; y < n; ++y)
            if (g[m[y]][y] != -INF) ans += g[m[y]][y];
        return ans;
    }
};
