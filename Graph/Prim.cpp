// Queries minimum path of spanning tree of a graph, where all vertices are connected, using Prim's algorithm.
// The n vertices are supposed to be marked [0, n); edge should have size n.
int minpath(const vector<vector<pii>>& edge) {
    const int N = edge.size();
    bool vis[N] = {0};
    priority_queue<pii, vector<pii>, greater<pii>> q;

    vis[0] = true;
    int nvis = 1;
    for (auto& e : edge[0]) q.push(e);

    while (nvis < N) {
        int d = q.top().first;
        int v = q.top().second;
        q.pop();
        if (vis[v]) continue;
        cout << d << endl;
        vis[v] = true;
        if (++nvis == N) return d;
        for (auto& e : edge[v]) {
            if (!vis[e.second]) q.emplace(d + e.first, e.second);
        }
    }
    throw "Never reaches here.";
}