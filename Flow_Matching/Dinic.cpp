class Dinic {
   private:
    struct edge { int d, r; ll c; };
    vector<vector<edge>> adj; vector<int> lv, ve; int n;
    bool mklv(int s, int d) {
        lv.assign(n, -1); lv[s] = 0; queue<int> q({s});
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto& e : adj[v]) {
                if (e.c == 0 || lv[e.d] != -1) continue;
                lv[e.d] = lv[v] + 1, q.push(e.d);
            }
        }
        return lv[d] > 0;
    }
    ll aug(int v, ll f, int d) {
        if (v == d) return f;
        for (; ve[v] < adj[v].size(); ve[v]++) {
            auto& e = adj[v][ve[v]];
            if (lv[e.d] != lv[v] + 1 || !e.c) continue;
            ll sent = aug(e.d, min(f, e.c), d);
            if (sent > 0) {
                e.c -= sent, adj[e.d][e.r].c += sent; 
                return sent;
            }
        } 
        return 0;
    }
   public:
    // 建空圖。 n 為節點數量 (含 source 和 sink)。
    Dinic(int n) : n(n + 1) { clear(); }
    void clear() { adj.assign(n, {}); }
    void add_edge(int src, int dst, ll cap) {
        edge ss{dst, (int)adj[dst].size(), cap};
        edge dd{src, (int)adj[src].size(), 0};
        adj[src].push_back(ss), adj[dst].push_back(dd);
    }
    ll max_flow(int s, int d) {
        ll ret = 0;
        while (mklv(s, d)) {
            ve.assign(n, 0);
            while (ll f = aug(s, inf, d)) ret += f;
        } 
        return ret;
    }
};