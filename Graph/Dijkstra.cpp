// Queries mininum path from src to dest in a graph where src and dest are connected.
// The n vertices are supposed to be marked [0, n); edge should have size n.
int dijkstra(int src, int dest, const vector<vector<pii>>& edge) {
    const int N = edge.size();
    bool nvis[N] = {0};
    // A comparator may be required.
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
    while (!q.empty()) {
        int v = q.top().second;
        int d = q.top().first;
        q.pop();
        if (v == dest) return d;
        if (nvis[v]) continue;
        nvis[v] = true;
        for (auto& e : edge[v]) {
            if (!nvis[e.second]) {
                // Fit the comparator
                q.emplace(d + e.first, e.second);
            }
        }
    }
    throw "src and dest are not connected.";
}

// Queries minuimum path from src to all the other vertices in a graph where all vertices are connected.
// The n vertices are supposed to be marked [0, n); edge should have size n.
vector<int> dijkstra(int src, const vector<vector<pii>>& edge) {
    const int N = edge.size();
    vector<int> mindist(N, -1);
    int nvis = 0;
    // A comparator may be required.
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
    while (nvis < N) {
        if (q.empty()) throw "Not all vertices connected.";
        int v = q.top().second;
        int d = q.top().first;
        q.pop();
        if (mindist[v] != -1) continue;
        mindist[v] = d;
        nvis++;
        for (auto& e : edge[v]) {
            if (mindist[e.second] == -1) {
                // Fit the comparator
                q.emplace(d + e.first, e.second);
            }
        }
    }
    return mindist;
}