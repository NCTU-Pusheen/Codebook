/** 問某點到所有圖上的點的最短距離。0/1-based 都安全。 edge 要
 * 是 {cost，dest} 格式。回傳的陣列若含有 -1 表示 src 到該位置
 * 不連通 **/
typedef pair<ll, int> pii;
vector<ll> dijkstra(int src, vector<vector<pii>>& edge) {
    vector<ll> sum(edge.size(), -1);
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
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
