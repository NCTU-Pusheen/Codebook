typedef pair<ll, ll> pii;
#define x first
#define y second
#define ii (i + 1) % n  // 打字加速！
pii operator-(const pii& a, const pii& b) {
    return {a.x - b.x, a.y - b.y};
}  // const 不可省略
ll cross(const pii& a, const pii& b) {
    return a.x * b.y - a.y * b.x;
}
ll crossfrom(const pii& o, const pii& a, const pii& b) {
    return cross(a - o, b - o);
}
ll dd(const pii& a, const pii& b) {
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// 給平面上任意個點，求其凸包。返回順序為逆時針。
vector<pii> makepoly(vector<pii>& pp) {
    int n = pp.size();
    sort(pp.begin(), pp.end());
    vector<pii> ret;
    for (int i = 0; i < n; i++) {
        while (ret.size() >= 2 &&
               crossfrom(ret[ret.size() - 2], ret.back(),
                         pp[i]) <= 0)
            ret.pop_back();
        ret.push_back(pp[i]);
    }
    for (int i = n - 2, t = ret.size() + 1; i >= 0; i--) {
        while (ret.size() >= t &&
               crossfrom(ret[ret.size() - 2], ret.back(),
                         pp[i]) <= 0)
            ret.pop_back();
        ret.push_back(pp[i]);
    }
    if (n >= 2) ret.pop_back();
    return ret;
}

// (shoelace formula)
// 給凸包，問其面積。若要問其面積的兩倍，則可以保證整數，請修改回傳值。
double area(vector<pii>& poly) {
    int n = poly.size();
    ll ans = 0;
    for (int i = 0; i < n; i++)
        ans += (poly[i].x * poly[ii].y);
    for (int i = 0; i < n; i++)
        ans -= (poly[i].y * poly[ii].x);
    return double(abs(ans)) / 2;
}

// 給凸包，問其兩點最遠距離。若要問平面上任意個點的兩點最遠距離，請先
// 轉成凸包。若要問距離平方，則可以保證為整數，請把兩處回傳值的
// sqrt 去除。
#define kk (k + 1) % n
double maxdist(vector<pii>& poly) {
    int k = 1, n = poly.size();
    if (n == 2) return sqrt(dd(poly[0], poly[1]));
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        while (
            abs(crossfrom(poly[kk], poly[i], poly[ii])) >=
            abs(crossfrom(poly[k], poly[i], poly[ii])))
            k = kk;
        ans = max(ans, max(dd(poly[i], poly[k]),
                           dd(poly[ii], poly[k])));
    }
    return sqrt(ans);
}
