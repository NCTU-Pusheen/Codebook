// 一般來說複雜度遠低於 O(EV^2) ， 二分圖約 O(E * sqrt(v)) 。
// 0/1-based 都安全。
class Dinic {
    struct edge {
        int d, r; ll c;
        edge(int d, ll c, int r) : d(d), c(c), r(r){};
    };
   private:
    vector<vector<edge>> adj; vector<int> lv, ve; int n;
    bool mklv(int s, int d) {
        lv.assign(n, -1); lv[s] = 0;
        queue<int> q; q.push(s);
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
    // 建立空圖， n 是節點 (包含 source, sink) 數量
    Dinic(int n) : n(n + 1) { clear(); }
    // 清空整個圖，這需要重複使用 dinic 時 (如二分搜) 很方便
    void clear() { adj.assign(n, vector<edge>()); }
    // 加有向邊 src->dst ，cap 是容量
    void add_edge(int src, int dst, ll cap) {
        edge ss(dst, cap, adj[dst].size());
        edge dd(src, 0, adj[src].size());
        adj[src].push_back(ss), adj[dst].push_back(dd);
    }
    ll max_flow(int s, int d) {
        ll ret = 0;
        while (mklv(s, d)) {
            ve.assign(n, 0);
            while (ll f = aug(s, 9e18, d)) ret += f;
        }
        return ret;
    }
};
