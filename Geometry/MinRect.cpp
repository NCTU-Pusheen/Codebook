// 全部浮點數運算，先製作凸包，然後呼叫 minrect
typedef long double dd;
typedef pair<dd, dd> pii;
#define x first
#define y second
#define in inline
#define cp const pii&
#define op operator
#define ab (cp a, cp b)
const dd eps = 1e-8;
in pii op+ab { return {a.x + b.x, a.y + b.y}; }
in pii op-ab { return {a.x - b.x, a.y - b.y}; }
in pii op*(cp p, dd v) { return {v * p.x, v * p.y}; }
in dd  op^ab { return a.x * b.x + a.y * b.y; }
in dd  op*ab { return a.x * b.y - a.y * b.x; }
in dd  op%ab {
    dd dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
in dd crzf(cp o, cp a, cp b) { return (a - o) * (b - o); }
in dd dotf(cp o, cp a, cp b) { return (a - o) ^ (b - o); }

#define judge \
    crzf(ret[ret.size() - 2], ret.back(), pp[i]) <= eps
vector<pii> makepoly(vector<pii>& pp) {
    sort(pp.begin(), pp.end());
    pp.erase(unique(pp.begin(), pp.end()), pp.end());
    int n = pp.size(); vector<pii> ret;
    for (int i = 0; i < n; i++) {
        while (ret.size() >= 2 && judge) ret.pop_back();
        ret.push_back(pp[i]);
    }
    for (int i = n - 2, s = ret.size() + 1; i >= 0; i--) {
        while (ret.size() >= s && judge) ret.pop_back();
        ret.push_back(pp[i]);
    }
    if (n >= 2) ret.pop_back(); return ret;
}

// 給凸包，問最小覆蓋矩形面積以及該矩形頂點座標 (存於 rec)
// 。頂點座標按照凸包製作方式排序。如果不需要矩形座標，把跟
// rec 有關的程式碼移除。
#define xx(i) ((i + 1) % n)
in pii foot(cp s1, cp s2, cp q) {
return s1 + (s2 - s1) * dotf(s1, s2, q) * (1 / (s1 % s2));
}
dd minrect(const vector<pii>& poly, vector<pii>& rec) {
    int n = poly.size(); if (n < 3) return 0;
    dd minn = 1e50; rec.resize(4);
    int j = 1, k = 1, r;
    for (int i = 0; i < n; i++) {
        while (crzf(poly[i], poly[xx(i)], poly[xx(j)]) -
               crzf(poly[i], poly[xx(i)], poly[j]) > -eps)
            j = xx(j);
        while (dotf(poly[i], poly[xx(i)], poly[xx(k)]) -
               dotf(poly[i], poly[xx(i)], poly[k]) > -eps)
            k = xx(k);
        if (i == 0) r = k;
        while (dotf(poly[i], poly[xx(i)], poly[xx(r)]) -
               dotf(poly[i], poly[xx(i)], poly[r]) < eps)
            r = xx(r);
        dd a = crzf(poly[i], poly[xx(i)], poly[j]) *
               (dotf(poly[i], poly[xx(i)], poly[k]) -
                dotf(poly[i], poly[xx(i)], poly[r])) /
               (poly[i] % poly[xx(i)]);
        a = abs(a); if (a < minn) { minn = a;
            rec[0] = foot(poly[i], poly[xx(i)], poly[r]);
            rec[1] = foot(poly[i], poly[xx(i)], poly[k]);
            pii toss = foot(poly[i], poly[xx(i)], poly[j]);
            rec[2] = poly[j] + rec[0] - toss;
            rec[3] = poly[j] + rec[1] - toss;
        }
    }
    rec = makepoly(rec); return minn;
}
