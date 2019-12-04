/** Min cost max flow 。0/1-based 都安全。 **/
class MCMF {
   private:
    struct edge { int to, r; ll rest, c; };
    int n; ll f = 0, c = 0;
    vector<vector<edge>> g;
    vector<int> pre, prel;
    bool run(int s, int t) {
        vector<ll> dis(n, inf); vector<bool> vis(n);
        dis[s] = 0; queue<int> q; q.push(s);
        while (q.size()) {
            int u = q.front(); q.pop(); vis[u] = 0;
            for (int i = 0; i < g[u].size(); i++) {
                int v = g[u][i].to; ll w = g[u][i].c;
                if (g[u][i].rest <= 0 ||
                    dis[v] <= dis[u] + w)
                    continue;
                pre[v] = u, prel[v] = i;
                dis[v] = dis[u] + w;
                if (!vis[v]) vis[v] = 1, q.push(v);
            }
        }
        if (dis[t] == inf) return 0;
        ll tf = inf;
        for (int v = t, u, l; v != s; v = u) {
            u = pre[v], l = prel[v];
            tf = min(tf, g[u][l].rest);
        }
        for (int v = t, u, l; v != s; v = u) {
            u = pre[v], l = prel[v], g[u][l].rest -= tf;
            g[v][g[u][l].r].rest += tf;
        }
        c += tf * dis[t], f += tf;
        return 1;
    }
   public:
    // 建立空圖，n 是節點數量 (包含 source 和 sink)
    MCMF(int n)
        : n(n + 1), g(n + 1), pre(n + 1), prel(n + 1) {}
    // 加有向邊 u->v ，cap 容量 cost 成本
    void add_edge(int u, int v, ll cap, ll cost) {
        g[u].push_back({v, (int)g[v].size(), cap, cost});
        g[v].push_back({u, (int)g[u].size() - 1, 0, -cost});
    }
    pair<ll, ll> query(int src, int sink) {
        while (run(src, sink));
        return {f, c};  //{min cost, max flow}
    }
};
