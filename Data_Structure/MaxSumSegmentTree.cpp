/** 計算最大子區間連續和的線段樹，限定 1-based 。
 * 複雜度 O(Q*log(N)) **/
#define ls i << 1
#define rs i << 1 | 1
class MaxSumSegmentTree {
   private:
    struct node {
        ll lss, rss, ss, ans;
        void set(ll v) { lss = rss = ss = ans = v; }
    };
    int n;
    vector<node> a;  // 萬萬不可用普通陣列，要用 vector
    vector<ll> z;
    void pull(int i) {
        a[i].ss = a[ls].ss + a[rs].ss;
        a[i].lss = max(a[ls].lss, a[ls].ss + a[rs].lss);
        a[i].rss = max(a[rs].rss, a[rs].ss + a[ls].rss);
        a[i].ans = max(max(a[ls].ans, a[rs].ans),
                       a[ls].rss + a[rs].lss);
    }
    void build(int i, int l, int r) {
        if (l == r) return a[i].set(z[l]), void();
        int m = (l + r) >> 1;
        build(ls, l, m), build(rs, m + 1, r), pull(i);
    }
    void set(int i, int l, int r, int q, ll v) {
        if (l == r) return a[i].set(v), void();
        int m = (l + r) >> 1;
        if (q <= m) set(ls, l, m, q, v);
        else set(rs, m + 1, r, q, v);
        pull(i);
    }
    node query(int i, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return a[i];
        int m = (l + r) >> 1;
        if (qr <= m) return query(ls, l, m, ql, qr);
        if (m < ql) return query(rs, m + 1, r, ql, qr);
        node lo = query(ls, l, m, ql, qr),
             ro = query(rs, m + 1, r, ql, qr), ans;
        ans.ss = lo.ss + ro.ss;
        ans.lss = max(lo.lss, lo.ss + ro.lss);
        ans.rss = max(ro.rss, ro.ss + lo.rss);
        ans.ans = max(max(lo.ans, ro.ans), lo.rss + ro.lss);
        return ans;
    }

   public:
    MaxSumSegmentTree(int n) : n(n) {
        a.resize(n << 2), z.resize(n << 2);
        build(1, 1, n);
    }
    // 單點設值。限定 1-based 。
    inline void set(int i, ll v) { set(1, 1, n, i, v); }
    // 問必區間 [l, r] 的最大子區間連續和。限定 1-based 。
    inline ll query(int l, int r) {
        return query(1, 1, n, l, r).ans;
    }
};
