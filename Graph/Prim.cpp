// 0/1-based n(必須剛好) edge:{cost, dest} 
typedef pair<ll, int> pii;
ll MST(vector<vector<pii>>& edge, int n) {
    vector<bool> vis(n + 1);
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, 1);
    ll ret = 0; int nvis = 0;
    while (nvis < n && q.size()) {
        ll d = q.top().first;
        int v = q.top().second; q.pop();
        if (vis[v]) continue;
        vis[v] = 1; ret += d;
        if (++nvis == n) return ret;
        for (auto& e : edge[v])
            if (!vis[e.second]) q.push(e);
    } return -1; // unconnected
}
