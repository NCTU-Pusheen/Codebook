#define x first
#define y second
// 看要做整數運算還是浮點數運算(甚至分數運算，請自行實作加減乘除)
// 若是整數運算，某些運算可能失真(如求兩直線交點)
#define T double

// 兩個 eq 選一個
inline bool eq(double a, double b) { return abs(a - b) < 1e-7; }
inline bool eq(long long a, long long b) { return a == b; }

#define point vec
struct vec {
    T x, y;  // 向量或坐標的x,y值
    vec operator+(vec o) { return {x + o.x, y + o.y}; }
    vec operator-(vec o) { return {x - o.x, y - o.y}; }
    vec operator*(T o) { return {x * o, y * o}; }
    vec operator/(T o) { return {x / o, y / o}; }
    T operator%(vec o) { return x * o.x + y * o.y; }      // 內積
    T operator*(vec o) { return x * o.y - y * o.x; }      // 外積
    T abs() { return x * x + y * y; }                     // 絕對值平方
    bool samedir(vec o) { return eq(x * o.y, y * o.x); }  // 兩向量方向是否相同或相反
};
vec makevec(point src, point dst) { return {dst.x - src.x, dst.y - src.y}; }

#define seg line
struct line {
    point s, t;  // 此直線經過s,t；或此線段始於s且止於t
    vec d;       // 此直線的向量
    T a, b, c;   // ax+by=c

    line(point p, point q) {  // 此直線經過p,q；或此線段為始於p且止於q
        s = p, t = q, d = makevec(p, q);
        a = p.y - q.y, b = q.x - p.x, c = a * p.x + b * p.y;
    }
    // 點是否在直線上
    bool passLine(point p) { return d.samedir(p - s); }
    bool passSeg(point p) { // 點是否在線段上
        vec ap = makevec(s, p), bp = makevec(t, p);
        return passLine(p) && ap % bp < 0;
    }
    // 兩直線是否重合
    bool sameLine(line o) { return d.samedir(o.d) && passLine(o.s); }
    // 兩直線是否平行且不重合
    bool para(line o) { return d.samedir(o.d) && !passLine(o.s); }
    point proj(point p) {  // 求某點在此直線上的投影座標
        vec e = {p - s};
        T t = e % d / d.abs();
        vec dst = {d.x * t, d.y * t};
        return s + dst;
    }
    // 點與直線距離平方
    T dist2(point p) { return (proj(p) - p).abs(); }
    // 兩平行直線距離平方
    T dist2(line o) { return (o.proj(s) - s).abs(); }
    // 此直線是否將兩點隔開
    bool split(point p, point q) { return (a * p.x + b * p.y < 0) != (a * q.x + b * q.y < 0); }
    // 兩非平行線段是否相交
    bool meet(seg o) { return split(o.s, o.t) && o.split(s, t); }
    point intersect(line o) {  // 兩非平行直線相交座標
        return {(c * o.b - b * o.c) / (a * o.b - b * o.a),
                (a * o.c - c * o.a) / (a * o.b - b * o.a)};
    }
    double cosangle(line o) {  // 兩直線夾角之 cos 值
        return (d % o.d) / (sqrt(d.abs() * o.d.abs()));
    }
};

#define rr (r * r)  // 半徑平方
#define usevars                                            \ //打字加速
    double x1 = c.x, x2 = o.c.x, y1 = c.y, y2 = o.c.y;     \
    double r1 = r, r2 = o.r, r12 = r1 * r1, r22 = r2 * r2; \
    double dx = x2 - x1, dy = y2 - y1, dd = dx * dx + dy * dy, d = sqrt(dd);
const double PI = acos(-1);
struct circle {
    point c;   // 圓心
    double r;  // 半徑
    // 求直線與圓的交點並回傳交點數量。若有兩點，存於ans1與ans2，若有一點，存於ans1。
    int meetLine(line l, point& ans1, point& ans2) {
        double d2 = l.dist2(c);
        if (eq(d2, rr)) return ans1 = l.proj(c), 1;  // 交於一點
        if (d2 > rr) return 0;                       // 無交點
        l = {l.s - c, l.t - c};
        double s = l.a * l.a + l.b * l.b, w = rr - l.c * l.c / s, m = sqrt(w / s);
        double x = -l.a * l.c / s, y = -l.b * l.c / s;
        ans1 = {x + l.b * m, y - l.a * m}, ans2 = {x - l.b * m, y + l.a * m};
        ans1 = ans1 + c, ans2 = ans2 + c;
        return 2;
    }
    // 求線段與圓的交點並回傳交點數量。
    int meetSeg(seg l, point& ans1, point& ans2) {
        int res = meetLine(l, ans1, ans2);
        if (res == 0) return 0;
        if (res == 1) return l.passSeg(ans1);
        return (int)l.passSeg(ans1) + l.passSeg(ans2);
    }
    // 求圓與圓的交點並回傳交點數量。
    int meetCircle(circle o, point& ans1, point& ans2) {
        usevars;
        if (d > r1 + r2) return 0;       // 互斥
        if (d < abs(r1 - r2)) return 0;  // 完全包含
        point A = {(x1 + x2) / 2, (y1 + y2) / 2};
        double f = (r12 - r22) / (2 * dd);
        point B = {dx * f, dy * f};
        double h = (r12 - r22);
        f = sqrt(2 * (r12 + r22) / dd - h * h / (dd * dd) - 1) / 2;
        point C = {dy * f, -dx * f};
        ans1 = A + B + C, ans2 = A + B - C;
        return eq(d, r1 + r2) ? 1 : 2;
    }
    double coverArea(circle o) { // 求兩圓重疊部分面積
        if (r < o.r) return o.coverArea(*this);
        usevars;
        if (d > r1 + r2) return 0;                  // 互斥
        if (d < abs(r1 - r2)) return PI * r2 * r2;  // 完全包含
        double d1 = (r12 - r22 + dd) / (2 * d), d2 = d - d1;
        return r12 * acos(d1 / r1) - d1 * sqrt(r12 - d1 * d1) + r22 * acos(d2 / r2) - d2 * sqrt(r22 - d2 * d2);
    }
};

double len(point a, point b) { return sqrt((a - b).abs()); } // 打字加速
struct tri {
    point a, b, c;
    T area2() { return abs((b - a) * (c - a)); }  // 求面積之兩倍
    point barycenter() { return (a + b + c) / 3; }  // 重心
    point perpencenter() { return barycenter() * 3 - circumcenter() * 2; } // 垂心
    point circumcenter() {  // 外心
        point p1 = (a + b) / 2, p2 = {p1.x - a.y + b.y, p1.y + a.x - b.x};
        line u = {p1, p2};
        p1 = (a + c) / 2, p2 = {p1.x - a.y + c.y, p1.y + a.x - c.x};
        line v = {p1, p2};
        return u.intersect(v);
    }
    point incentre() {  // 內心
        T A = len(b, c), B = len(a, c), C = len(a, b);
        point p = {A * a.x + B * b.x + C * c.x, A * a.y + B * b.y + C * c.y};
        return p / (A + B + C);
    }
    // 費馬點
    // 若有一角 >= 120 (cos(x) <= -0.5) ，費馬點為該角對應的點
    // 否則三角型三條邊對外做正三角形，得到三個頂點 A', B', C'
    // 費馬點為 AA' BB' CC' 三線之交點
};