/**
 * Queries mininum path from src to dst in a graph where src and dst are connected. 0- or 1-based are safe without any changes. Value
 * pairs put in the edge vector are of format {edge length, adjacent vertex}. If ll type is required for path length, replaces pii with
 * pair<ll, int> and return type with ll.
 */
int dijkstra(int src, int dst, vector<vector<pii>>& edge) {  // return type may be int or ll
    bool nvis[edge.size()];
    memset(nvis, 0, sizeof(nvis));
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
    while (1) {
        int v = q.top().second;
        auto d = q.top().first;  // may be int or ll
        q.pop();
        if (v == dst) return d;
        if (nvis[v]) continue;
        nvis[v] = true;
        for (auto& e : edge[v])
            if (!nvis[e.second]) q.emplace(d + e.first, e.second);
    }
    // Reach here indicates src and dst are not connected
}

/**
 * Queries minuimum path from src to all the other vertices in a graph where all vertices are connected. Arg n is count of vertices in
 * the graph, while 0- or 1-based are both safe without any changes.  Value pairs put in the edge vector are of format {edge length,
 * adjacent vertex}. If ll type is required for edge length, replaces pii with pair<ll, int> and vector<int> with vector<ll>.
 */
vector<int> dijkstra(int src, vector<vector<pii>>& edge) {  // return type may be int or ll
    int nvis = 0;
    vector<int> sum(edge.size(), -1);  // may be int or ll
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
    while (!q.empty()) {
        int v = q.top().second;
        auto d = q.top().first;  // may be int or ll
        q.pop();
        if (sum[v] != -1) continue;
        sum[v] = d;
        nvis++;
        for (auto& e : edge[v])
            if (sum[e.second] == -1) q.emplace(d + e.first, e.second);
    }
    return sum;
}