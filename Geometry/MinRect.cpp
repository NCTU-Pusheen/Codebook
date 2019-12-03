typedef double ll;  // 別用 long long 吧
typedef pair<double, double> pii;
#define x first
#define y second
#define xx(i) ((i + 1) % n)
inline pii operator+(const pii& a, const pii& b) {
    return pii(a.x + b.x, a.y + b.y);
}
inline pii operator-(const pii& a, const pii& b) {
    return pii(a.x - b.x, a.y - b.y);
}  // const 不可省略
inline ll operator*(const pii& a, const pii& b) {
    return a.x * b.y - a.y * b.x;
}
inline ll operator%(const pii& a, const pii& b) {
    return a.x * b.x + a.y * b.y;
}
inline ll crzf(const pii& o, const pii& a, const pii& b) {
    return (a - o) * (b - o);
}
inline ll dotf(const pii& o, const pii& a, const pii& b) {
    return (a - o) % (b - o);
}
inline ll dd(const pii& a, const pii& b) {
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// 給凸包，問其最小覆蓋矩形。注意，這個檔案很多變數可能跟旋轉卡尺撞
// 名，可以考慮用 namespace 區別
inline ll minrect(const vector<pii>& poly) {
    int n = poly.size();
    if (n < 3) return 0;
    ll ans = 1e18;
    int j = 1, k = 1, r;
    for (int i = 0; i < n; i++) {
        while (crzf(poly[i], poly[xx(i)], poly[xx(j)]) -
                   crzf(poly[i], poly[xx(i)], poly[j]) >
               0)
            j = xx(j);
        while (dotf(poly[i], poly[xx(i)], poly[xx(k)]) -
                   dotf(poly[i], poly[xx(i)], poly[k]) >
               0)
            k = xx(k);
        if (i == 0) r = j;
        while (dotf(poly[i], poly[xx(i)], poly[xx(r)]) -
                   dotf(poly[i], poly[xx(i)], poly[r]) <
               0)
            r = xx(r);
        ll den = dd(poly[i], poly[xx(i)]);
        ll num = crzf(poly[i], poly[xx(i)], poly[j]) *
                 (dotf(poly[i], poly[xx(i)], poly[k]) -
                  dotf(poly[i], poly[xx(i)], poly[r]));
        ll a = num / den;
        ans = min(a, ans);
    }
    return ans;
}
