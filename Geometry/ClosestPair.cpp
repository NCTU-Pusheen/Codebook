typedef pair<ll, ll> pii;
#define x first
#define y second
ll dd(const pii& a, const pii& b) {
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
const ll inf = 1e18;
ll dac(vector<pii>& p, int l, int r) {
    if (l >= r) return inf;
    int m = (l + r) / 2;
    ll d = min(dac(p, l, m), dac(p, m + 1, r));
    vector<pii> t;
    for (int i = m; i >= l && p[m].x - p[i].x < d; i--)
        t.push_back(p[i]);
    for (int i = m + 1; i <= r && p[i].x - p[m].x < d; i++)
        t.push_back(p[i]);
    sort(t.begin(), t.end(),
         [](pii& a, pii& b) { return a.y < b.y; });
    int n = t.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 1; j < 4 && i + j < n; j++)
            // 這裡可以知道是哪兩點是最小點對
            d = min(d, dd(t[i], t[i + j]));
    return d;
}
// 給一堆點，求最近點對的距離「的平方」。
ll closest_pair(vector<pii>& pp) {
    sort(pp.begin(), pp.end());
    return dac(pp, 0, pp.size() - 1);
}
