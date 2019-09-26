/**
 * Queries mininum path from src to dest in a graph where src and dest are connected. 0- or 1-based are safe without any changes. Value
 * pairs put in the edge vector are of format {edge length, adjacent vertex}. If ll type is required for path length, replaces pii with
 * pair<ll, int> and return type with ll.
 */
int dijkstra(int src, int dest, vector<vector<pii>>& edge) {  // return type may be int or ll
    int n = edge.size();
    bool nvis[n];
    memset(nvis, 0, sizeof(nvis));
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
    while (1) {
        int v = q.top().second;
        auto d = q.top().first;  // may be int or ll
        q.pop();
        if (v == dest) return d;
        if (nvis[v]) continue;
        nvis[v] = true;
        for (auto& e : edge[v])
            if (!nvis[e.second]) q.emplace(d + e.first, e.second);
    }
    // Reach here indicates src and dest are not connected
}

/**
 * Queries minuimum path from src to all the other vertices in a graph where all vertices are connected. Arg n is count of vertices in
 * the graph, while 0- or 1-based are both safe without any changes.  Value pairs put in the edge vector are of format {edge length,
 * adjacent vertex}. If ll type is required for edge length, replaces pii with pair<ll, int> and vector<int> with vector<ll>.
 */
vector<int> dijkstra(int src, vector<vector<pii>>& edge, int n) {  // return type may be int or ll
    int nvis = 0;
    vector<int> mindist(edge.size(), -1);  // may be int or ll
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
    while (nvis < n) {
        int v = q.top().second;
        auto d = q.top().first;  // may be int or ll
        q.pop();
        if (mindist[v] != -1) continue;
        mindist[v] = d;
        nvis++;
        for (auto& e : edge[v])
            if (mindist[e.second] == -1) q.emplace(d + e.first, e.second);
    }
    return mindist;
}