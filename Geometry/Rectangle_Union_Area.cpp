const int maxn = 1e5 + 10;
struct rec{
    int t, b, l, r;
} r[maxn];
int n, cnt[maxn << 2];
long long st[maxn << 2], ans = 0;
vector<int> x, y;
vector<pair<pair<int, int>, pair<int, int>>> v;
void modify(int t, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) cnt[t] += v;
    else {
        int m = (l + r) >> 1;
        if (qr <= m) modify(t << 1, l, m, ql, qr, v);
        else if (ql >= m) modify(t << 1 | 1, m, r, ql, qr, v);
        else modify(t << 1, l, m, ql, m, v), modify(t << 1 | 1, m, r, m, qr, v);
    }
    if (cnt[t]) st[t] = y[r] - y[l];
    else if (r - l == 1) st[t] = 0;
    else st[t] = st[t << 1] + st[t << 1 | 1];
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> r[i].l >> r[i].r >> r[i].b >> r[i].t;
        if (r[i].l > r[i].r) swap(r[i].l, r[i].r);
        if (r[i].b > r[i].t) swap(r[i].b, r[i].t);
        x.push_back(r[i].l);
        x.push_back(r[i].r);
        y.push_back(r[i].b);
        y.push_back(r[i].t);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end()); 
    for (int i = 0; i < n; i++) {
        r[i].l = lower_bound(x.begin(), x.end(), r[i].l) - x.begin();
        r[i].r = lower_bound(x.begin(), x.end(), r[i].r) - x.begin();
        r[i].b = lower_bound(y.begin(), y.end(), r[i].b) - y.begin();
        r[i].t = lower_bound(y.begin(), y.end(), r[i].t) - y.begin();
        v.emplace_back(make_pair(r[i].l, 1), make_pair(r[i].b, r[i].t));
        v.emplace_back(make_pair(r[i].r, -1), make_pair(r[i].b, r[i].t));
    }
    sort(v.begin(), v.end(), [](pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b){
        if (a.first.first != b.first.first) return a.first.first < b.first.first;
        return a.first.second > b.first.second;
    });
    for (int i = 0; i < v.size(); i++) {
        if (i) ans += (x[v[i].first.first] - x[v[i - 1].first.first]) * st[1];
        modify(1, 0, y.size(), v[i].second.first, v[i].second.second, v[i].first.second);
    }
    cout << ans << '\n';
    return 0;
}
