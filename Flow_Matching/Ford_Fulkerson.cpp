const int maxn = 1e5 + 10, INF = 1e9;
const long long INF64 = 1e18;
struct edge{ int to, cap, rev; };
vector<edge> G[maxn];
int n, m, s, t, a, b, c;
bool vis[maxn];
int dfs(int v, int t, int f) {
    cout << v << ' ' << t << ' ' << f << '\n';
    if (v == t) return f;
    vis[v] = true;
    for (edge &e: G[v]) {
        if (!vis[e.to] && e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d, G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
int ford_fulkerson(int s, int t) {
    int flow = 0, f;
    for (int i = 0; i < n; i++) {
        cout << i << " : ";
        for (edge e: G[i])
            cout << '(' << e.to << ',' << e.cap << ')' << ' ';
        cout << '\n';
    }
    do {
        memset(vis, false, sizeof(vis));
        f = dfs(s, t, INF);
        for (int i = 0; i < n; i++) {
            cout << i << " : ";
            for (edge e: G[i])
                cout << '(' << e.to << ',' << e.cap << ')' << ' ';
            cout << '\n';
        }
        cout << f << '\n';
        flow += f;
    } while (f > 0);
    return flow;
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
    cout << ford_fulkerson(s, t) << '\n';
    return 0;
}
