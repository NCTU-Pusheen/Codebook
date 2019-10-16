/**
 * Queries minimum path of spanning tree of a graph using
 * Prim's algorithm. If the graph is disconnected, -1 is
 * returned. Arg n is the count of vertices in the graph,
 * while 0- or 1-based are both safe without any changes.
 * Value pairs put in edge vectors are of format {edge
 * weight, adjacent vertex}.
 */
typedef pair<ll, int> pii;
ll minpath(vector<vector<pii>>& edge, int n) {
    vector<bool> vis(n + 1);
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, 1);
    ll ret = 0;
    int nvis = 0;

    while (nvis < n && q.size()) {
        ll d = q.top().first;
        int v = q.top().second;
        q.pop();
        if (vis[v]) continue;
        vis[v] = 1;
        ret += d;
        if (++nvis == n) return ret;
        for (auto& e : edge[v]) {
            if (!vis[e.second]) q.push(e);
        }
    }
    return -1;
}