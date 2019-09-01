const int maxn = 1e5 + 10;
const int INF = 1e9;
const long long INF64 = 1e18;
struct edge{
    int to, cap, rev;
};
vector<edge> G[maxn];
int n, m, s, t, a, b, c, iter[maxn], level[maxn];
void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (edge e: G[u]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }
}
int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
int dinic(int s, int t) {
    int flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0)
            flow += f;
    }
}
void init(int n) {
    for (int i = 0; i < n; i++) G[i].clear();
}
int main() {
    cin >> n >> m >> s >> t;
    init(n);
    while (m--) {
        cin >> a >> b >> c;
        G[a].push_back((edge){b, c, (int)G[b].size()});
        G[b].push_back((edge){a, 0, (int)G[a].size() - 1});
    }
    cout << dinic(s, t) << '\n';
    return 0;
}
