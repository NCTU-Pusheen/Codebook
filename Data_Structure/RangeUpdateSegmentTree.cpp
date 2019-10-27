#define ls i << 1
#define rs i << 1 | 1
const ll rr = 0x6891139;  // 亂數
class RangeUpdateSegmentTree {
   private:
    // 若不需要區間和，刪除所有含有 .s 的行
    // 若不需要 max/min ，刪除所有含有 .mx/.mn 的行
    struct node {
        int l, r, inc = 0, mod = rr;
        ll s = 0, mx = 0, mn = 0;
    };
    vector<node> a;
    int n;
    void push(int i) {
        // 複製貼上行加速
        if (a[i].mod != rr) {
            a[ls].mod = a[rs].mod = a[i].mod;
            a[ls].inc = a[rs].inc = 0;
            a[ls].mn = a[rs].mn = a[i].mod;
            a[ls].mx = a[rs].mx = a[i].mod;
            a[ls].s = (a[ls].r - a[ls].l + 1) * a[i].mod;
            a[rs].s = (a[rs].r - a[rs].l + 1) * a[i].mod;
            a[i].mod = rr;
        }
        if (a[i].inc) {
            a[ls].inc += a[i].inc, a[rs].inc += a[i].inc;
            a[ls].mn += a[i].inc, a[rs].mn += a[i].inc;
            a[ls].mx += a[i].inc, a[rs].mx += a[i].inc;
            a[ls].s += a[i].inc * (a[ls].r - a[ls].l + 1);
            a[rs].s += a[i].inc * (a[rs].r - a[rs].l + 1);
            a[i].inc = 0;
        }
    }
    void pull(int i) {
        a[i].s = a[ls].s + a[rs].s;
        a[i].mx = max(a[ls].mx, a[rs].mx);
        a[i].mn = min(a[ls].mn, a[rs].mn);
    }
    void build(int l, int r, int i) {
        a[i].l = l, a[i].r = r;
        if (l == r) return;
        int m = (l + r) >> 1;
        build(l, m, ls), build(m + 1, r, rs);
    }

   public:
    RangeUpdateSegmentTree(int n) : n(n), a(n << 2) {
        build(1, n, 1);
    }
    void set(int l, int r, ll val, int i = 1) {
        if (a[i].l >= l && a[i].r <= r) {
            a[i].s = val * (a[i].r - a[i].l + 1);
            a[i].mn = val = a[i].mx = a[i].mod = val;
            a[i].inc = 0;
            return;
        }
        push(i);
        int m = (a[i].l + a[i].r) >> 1;
        if (l <= m) set(l, r, val, ls);
        if (r > m) set(l, r, val, rs);
        pull(i);
    }
    void add(int l, int r, ll val, int i = 1) {
        if (a[i].l >= l && a[i].r <= r) {
            a[i].s += val * (a[i].r - a[i].l + 1);
            a[i].mn += val, a[i].mx += val, a[i].inc += val;
            return;
        }
        push(i);
        int m = (a[i].l + a[i].r) >> 1;
        if (l <= m) add(l, r, val, ls);
        if (r > m) add(l, r, val, rs);
        pull(i);
    }

    // 以下三函數幾乎雷同，請善用複製貼上
    ll maxx(int l, int r, int i = 1) {
        if (l <= a[i].l && a[i].r <= r) return a[i].mx;
        push(i);
        ll ret = -9e18;
        int m = (a[i].l + a[i].r) >> 1;
        if (l <= m) ret = max(ret, maxx(l, r, ls));
        if (r > m) ret = max(ret, maxx(l, r, rs));
        pull(i);
        return ret;
    }
    ll minn(int l, int r, int i = 1) {
        if (l <= a[i].l && a[i].r <= r) return a[i].mn;
        push(i);
        ll ret = 9e18;
        int m = (a[i].l + a[i].r) >> 1;
        if (l <= m) ret = min(ret, minn(l, r, ls));
        if (r > m) ret = min(ret, minn(l, r, rs));
        pull(i);
        return ret;
    }
    ll sum(int l, int r, int i = 1) {
        if (l <= a[i].l && a[i].r <= r) return a[i].s;
        push(i);
        ll ret = 0;
        int m = (a[i].l + a[i].r) >> 1;
        if (l <= m) ret += sum(l, r, ls);
        if (r > m) ret += sum(l, r, rs);
        pull(i);
        return ret;
    }
};
