
/**
 * Queries count of maximal flow. In a tie-break, queries
 * the minimal cost.
 */
class MCMF {
   private:
    struct edge {
        int to, r;
        ll rest, c;
    };
    int n;
    vector<vector<edge>> g;
    ll f = 0, c = 0;
    vector<int> pre, prel;

    bool run(int s, int t) {
        vector<ll> dis(n, inf);
        vector<bool> vis(n);
        dis[s] = 0;
        queue<int> q;
        q.push(s);
        while (q.size()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (int i = 0; i < g[u].size(); i++) {
                int v = g[u][i].to;
                ll w = g[u][i].c;
                if (g[u][i].rest <= 0 ||
                    dis[v] <= dis[u] + w)
                    continue;
                pre[v] = u;
                prel[v] = i;
                dis[v] = dis[u] + w;
                if (!vis[v]) vis[v] = 1, q.push(v);
            }
        }

        if (dis[t] == inf) return 0;

        ll tf = inf;
        for (int v = t, u, l; v != s; v = u) {
            u = pre[v];
            l = prel[v];
            tf = min(tf, g[u][l].rest);
        }
        for (int v = t, u, l; v != s; v = u) {
            u = pre[v];
            l = prel[v];
            g[u][l].rest -= tf;
            g[v][g[u][l].r].rest += tf;
        }
        c += tf * dis[t];
        f += tf;
        return 1;
    }

   public:
    // Constructs an empty graph.
    MCMF(int n)
        : n(n + 1), g(n + 1), pre(n + 1), prel(n + 1) {}
    // Adds an edge into the graph.
    void add_edge(int u, int v, ll cap, ll cost) {
        g[u].push_back({v, (int)g[v].size(), cap, cost});
        g[v].push_back({u, (int)g[u].size() - 1, 0, -cost});
    }
    // Queries the minimal cost and maximal flow.
    pair<ll, ll> query(int s, int t) {
        while (run(s, t));
        return {f, c};
    }
};
