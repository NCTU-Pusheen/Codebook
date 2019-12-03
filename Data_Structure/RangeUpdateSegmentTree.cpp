/**
 * 修改功能最強的線段樹，但只能查詢區間和以及極值，所有區間操作都
 * 是閉區間。只支援 1-based 。 **/
#define ls i << 1
#define rs i << 1 | 1
const ll rr = 0x6891139;  // 亂數，若跟題目碰撞會吃 WA 或 RE
class RangeUpdateSegmentTree {
   private:
    // 程式碼重複性略高 (已盡力)。若不需要區間和，刪除所有含有 .s
    // 的行；若不需要 max ，刪除所有含有 .x 的行。
    struct node {
        int l, r, adt = 0, stt = rr; ll s = 0, x = 0;
    };
    vector<node> a; // 萬萬不可以用普通陣列，要用 vector
    void push(int i) {
        if (a[i].stt != rr) {
            a[ls].stt = a[rs].stt = a[i].stt;
            a[ls].adt = a[rs].adt = 0;
            a[ls].x = a[rs].x = a[i].stt;
            a[ls].s = (a[ls].r - a[ls].l + 1) * a[i].stt;
            a[rs].s = (a[rs].r - a[rs].l + 1) * a[i].stt;
            a[i].stt = rr;
        }
        if (a[i].adt) {
            a[ls].adt += a[i].adt, a[rs].adt += a[i].adt;
            a[ls].x += a[i].adt, a[rs].x += a[i].adt;
            a[ls].s += a[i].adt * (a[ls].r - a[ls].l + 1);
            a[rs].s += a[i].adt * (a[rs].r - a[rs].l + 1);
            a[i].adt = 0;
        }
    }
    void pull(int i) {
        a[i].s = a[ls].s + a[rs].s;
        a[i].x = max(a[ls].x, a[rs].x);
    }
    void build(int l, int r, int i) {
        a[i].l = l, a[i].r = r;
        if (l == r) return;
        int stt = (l + r) >> 1;
        build(l, stt, ls), build(stt + 1, r, rs);
    }

   public:
    RangeUpdateSegmentTree(int n) : a(n << 2) {
        build(1, n, 1);
    }
    // 區間設值。注意只支援 1-based
    void set(int l, int r, ll val, int i = 1) {
        if (a[i].l >= l && a[i].r <= r) {
            a[i].s = val * (a[i].r - a[i].l + 1);
            a[i].x = a[i].stt = val;
            a[i].adt = 0;
            return;
        }
        push(i);
        int stt = (a[i].l + a[i].r) >> 1;
        if (l <= stt) set(l, r, val, ls);
        if (r > stt) set(l, r, val, rs);
        pull(i);
    }
    // 區間增值。注意只支援 1-based
    void add(int l, int r, ll val, int i = 1) {
        if (a[i].l >= l && a[i].r <= r) {
            a[i].s += val * (a[i].r - a[i].l + 1);
            a[i].x += val;
            a[i].adt += val;
            return;
        }
        push(i);
        int stt = (a[i].l + a[i].r) >> 1;
        if (l <= stt) add(l, r, val, ls);
        if (r > stt) add(l, r, val, rs);
        pull(i);
    }
    // 求區間最大值。注意只支援 1-based 。
    ll maxx(int l, int r, int i = 1) {
        if (l <= a[i].l && a[i].r <= r) return a[i].x;
        push(i);
        ll ret = -9e18;
        int stt = (a[i].l + a[i].r) >> 1;
        if (l <= stt) ret = max(ret, maxx(l, r, ls));
        if (r > stt) ret = max(ret, maxx(l, r, rs));
        pull(i);
        return ret;
    }
    // 求區間總和。注意只支援 1-based 。
    ll sum(int l, int r, int i = 1) {
        if (l <= a[i].l && a[i].r <= r) return a[i].s;
        push(i);
        ll ret = 0;
        int stt = (a[i].l + a[i].r) >> 1;
        if (l <= stt) ret += sum(l, r, ls);
        if (r > stt) ret += sum(l, r, rs);
        pull(i);
        return ret;
    }
};
