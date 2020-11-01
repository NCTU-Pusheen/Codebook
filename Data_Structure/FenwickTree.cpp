// 普通 BIT 只支援 1-based
const int maxn = ? ;
class BIT {
   private:
    ll a[maxn];
    ll sum(int i) {
        ll r = 0;
        while (i > 0) r += a[i], i -= i & -i;
        return r;
    }
   public:
    BIT() { memset(a, 0, sizeof(a)); }
    void add(int i, ll v) {
        while (i < maxn) a[i] += v, i += i & -i;
    }
    ll sum(int l, int r) { return sum(r) - sum(l - 1); }
};
// 區間加值 BIT 只支援 1-based   O(Q*log(N)) 閉區間
class RangeUpdateBIT {
   private:
    ll d[maxn], dd[maxn];
    ll sum(int i) {
        ll s = 0, ss = 0;
        int c = i + 1;
        while (i > 0) s += d[i], ss += dd[i], i -= i & -i;
        return c * s - ss;
    }
    void add(int i, ll v) {
        int c = i;
        while (i < maxn)
            d[i] += v, dd[i] += c * v, i += i & -i;
    }
   public:
    RangeUpdateBIT() {
        memset(d, 0, sizeof(d));
        memset(dd, 0, sizeof(dd));
    }
    ll sum(int l, int r) { return sum(r) - sum(l - 1); }
    void add(int l, int r, ll v) {
        add(l, v), add(r + 1, -v);
    }
};
