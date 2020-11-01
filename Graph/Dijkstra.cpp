// 0/1-based, edge = {cost，dest}, -1 : unconnected
typedef pair<ll, int> pii;
vector<ll> dijkstra (int s, vector<vector<pii>>& edge) {
    vector<ll> sum(edge.size(), -1);
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, s);
    while (q.size()) {
        int v = q.top().second; ll d = q.top().first;
        q.pop();
        if (sum[v] != -1) continue;
        sum[v] = d;
        for (auto& e : edge[v])
            if (sum[e.second] == -1)
                q.emplace(d + e.first, e.second);
    } return sum;
}
