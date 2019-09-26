// Queries minimum path of spanning tree of a graph, where all vertices are connected, using Prim's algorithm. Arg n is the count of
// vertices in the graph, while 0- or 1-based are both safe without any cahanges. The n vertices are supposed to be marked [0, n); edge
// should have size n. Value pairs put in edge vectors are of format {edge length, adjacent vertex}. If distance may have type ll,
// replace pii with pair<ll, int> and return type with ll.
int minpath(vector<vector<pii>>& edge, int n) {  // return type may be int or ll
    bool vis[edge.size()];
    priority_queue<pii, vector<pii>, greater<pii>> q;

    vis[0] = true;
    int nvis = 1;
    for (auto& e : edge[0]) q.push(e);

    while (nvis < n) {
        auto d = q.top().first;  // may be int or ll
        int v = q.top().second;
        q.pop();
        if (vis[v]) continue;
        cout << d << endl;
        vis[v] = true;
        if (++nvis == n) return d;
        for (auto& e : edge[v]) {
            if (!vis[e.second]) q.emplace(d + e.first, e.second);
        }
    }
    // Reach here indicates src and dest are not connected
}