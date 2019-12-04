/** 二分圖最大權值匹配 KM 演算法，複雜度 O(n^3)*/
#define inf 5e18
class KM {
   private:
    const vector<vector<ll>>& e;
    int xx, yy;
    vector<ll> cx, cy, wx, wy;
    vector<bool> vx, vy;
    ll z;

    bool dfs(int u) {
        vx[u] = 1;
        for (int v = 0; v < yy; v++) {
            if (vy[v] || e[u][v] == inf) continue;
            ll t = wx[u] + wy[v] - e[u][v];
            if (t == 0) {
                vy[v] = 1;
                if (cy[v] == -1 || dfs(cy[v])) {
                    cx[u] = v, cy[v] = u;
                    return 1;
                }
            } else if (t > 0)
                z = min(z, t);
        }
        return 0;
    }
   public:
    // 問最大匹配權重。
    ll max_weight() {
        for (int i = 0; i < xx; i++)
            for (int j = 0; j < yy; j++) {
                if (e[i][j] == inf) continue;
                wx[i] = max(wx[i], e[i][j]);
            }
        for (int i = 0; i < xx; i++) {
            while (1) {
                z = inf, vx.assign(xx, 0), vy.assign(yy, 0);
                if (dfs(i)) break;
                for (int j = 0; j < xx; j++)
                    if (vx[j]) wx[j] -= z;
                for (int j = 0; j < yy; j++)
                    if (vy[j]) wy[j] += z;
            }
        }
        ll ans = 0;
        for (int i = 0; i < xx; i++)
            if (cx[i] != -1) ans += e[i][cx[i]];
        return ans;
    }
    // 給他 n * m 的權重表 (n <= m)，求最大完全匹配權重，權重可以
    // 是負數。注意 n > m 會導致無窮迴圈。
    KM(vector<vector<ll>>& e) : e(e) {
        xx = e.size(), yy = e[0].size();  // xx 要 <= yy !!
        cx.assign(xx, -1), cy.assign(yy, -1);
        wx.assign(xx, 0), wy.assign(yy, 0);
    }
};
