/**
 * Queries mininum path from src to dst in a graph where src and dst are connected. 0- or 1-based are safe without any changes. Value
 * pairs put in the edge vector are of format {edge weight, adjacent vertex}.
 */
typedef pair<ll, int> pii;
ll dijkstra(int src, int dst, vector<vector<pii>>& edge) {
    vector<bool> vis(edge.size());
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
    while (q.size()) {
        int v = q.top().second;
        ll d = q.top().first;
        q.pop();
        if (v == dst) return d;
        if (vis[v]) continue;
        vis[v] = 1;
        for (auto& e : edge[v])
            if (!nvis[e.second]) q.emplace(d + e.first, e.second);
    }
    return -1;
}

/**
 * Queries minuimum path from src to all the other vertices in a graph where all vertices are connected. Arg n is count of vertices in
 * the graph, while 0- or 1-based are both safe without any changes. Value pairs put in the edge vector are of format {edge weight,
 * adjacent vertex}.
 */
typedef pair<ll, int> pii;
vector<ll> dijkstra(int src, vector<vector<pii>>& edge) {
    vector<ll> sum(edge.size(), -1);
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
    while (q.size()) {
        int v = q.top().second;
        ll d = q.top().first;
        q.pop();
        if (sum[v] != -1) continue;
        sum[v] = d;
        for (auto& e : edge[v])
            if (sum[e.second] == -1) q.emplace(d + e.first, e.second);
    }
    return sum;
}