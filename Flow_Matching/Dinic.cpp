/**
 * A dinic can find maximal count of flows in O(EV^2) in
 * general, while in biparitite O(E * sqrt(v)). All
 * arguments are safe for both 0- and 1-based cases without
 * any changes.
 */
class Dinic {
    struct edge {
        int d, r;
        ll c;
        edge(int d, ll c, int r) : d(d), c(c), r(r){};
    };

   private:
    vector<vector<edge>> adj;
    vector<int> lv;
    vector<int> ve;
    int n;

    bool mklv(int s, int d) {
        lv.assign(n, -1);
        queue<int> q;
        q.push(s);
        lv[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& e : adj[v]) {
                if (e.c == 0 || lv[e.d] != -1) continue;
                lv[e.d] = lv[v] + 1;
                q.push(e.d);
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
                e.c -= sent;
                adj[e.d][e.r].c += sent;
                return sent;
            }
        }
        return 0;
    }

   public:
    // Constructs a graph who has at most n vertices,
    // inclusive of source and sink. This graph has no edges
    // until you call add_edge function. Noted that all
    // vertices, including source and sink, should have
    // indcies in range [0, n].
    Dinic(int n) : n(n + 1) { clear(); }

    // Removes all edges from this graph.
    void clear() { adj.assign(n, vector<edge>()); }

    // Adds a directed edge into the graph, where arg s
    // indicates source, d destination, c capacity.
    void add_edge(int s, int d, ll c) {
        edge ss(d, c, adj[d].size());
        edge dd(s, 0, adj[s].size());
        adj[s].push_back(ss);
        adj[d].push_back(dd);
    }

    // Queries the maximal count of flows. Args s and d are
    // source and destination (sink).
    ll max_flow(int s, int d) {
        ll ret = 0;
        while (mklv(s, d)) {
            ve.assign(n, 0);
            while (ll f = aug(s, LLONG_MAX, d)) ret += f;
        }
        return ret;
    }
};