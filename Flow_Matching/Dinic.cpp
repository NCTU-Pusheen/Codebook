#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
const double PI = acos(-1);
#define x first
#define y second
#define iter(c) c.begin(), c.end()
#define ms(a) memset(a, 0, sizeof(a))
#define mss(a) memset(a, -1, sizeof(a))
#define mp(e, f) make_pair(e, f)

class dinic {
    struct edge {
        int dst;
        ll cap;
        int rev;
        edge(int d, ll c, int r) : dst(d), cap(c), rev(r){};
    };

   private:
    vector<vector<edge>> adj;
    vector<int> level;
    vector<int> vis_edge;
    int n;

    bool judge_level(int src, int dst) {
        level.assign(n, -1);
        queue<int> q;
        q.push(src);
        level[src] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& e : adj[v]) {
                if (e.cap == 0 || level[e.dst] != -1) continue;
                level[e.dst] = level[v] + 1;
                q.push(e.dst);
            }
        }
        return level[dst] > 0;
    }

    ll flow(int v, ll f, int dst) {
        if (v == dst) return f;
        for (; vis_edge[v] < adj[v].size(); vis_edge[v]++) {
            edge& e = adj[v][vis_edge[v]];
            if (level[e.dst] != level[v] + 1 || e.cap == 0) continue;
            ll sent = flow(e.dst, min(f, e.cap), dst);
            if (sent > 0) {
                e.cap -= sent;
                adj[e.dst][e.rev].cap += sent;
                return sent;
            }
        }
        return 0;
    }

   public:
    dinic(int n) : n(n + 1) { clear(); }

    void clear() { adj.assign(n, vector<edge>()); }

    void add_edge(int src, int dst, ll cap) {
        edge s(dst, cap, adj[dst].size()); 
        edge d(src, 0, adj[src].size());
        adj[src].push_back(s);
        adj[dst].push_back(d);
    }

    ll maxflow(int src, int dst) {
        ll ret = 0;
        while (judge_level(src, dst)) {
            vis_edge.assign(n, 0);
            while (ll f = flow(src, 1e18, dst)) ret += f;
        }
        return ret;
    }
};