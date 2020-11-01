vector<pii> G[maxn];
int dis[maxn]; bool inque[maxn];
void SPFA (int n, int s) { //O(kE) k~2.
    for(int i = 1; i <= n; i++) dis[i] = INF;
    queue<int> q; q.push(s); dis[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop(); inque[u] = 0;
        for (pii e : G[u]) {
            int v = e.first , w = e.second;
            if( dis[u] + w < dis[v]) {
                if (!inque[v]) q.push(v), inque[v] = true;
                dis[v] = dis[u] + w;
            }
        }
    }
}
