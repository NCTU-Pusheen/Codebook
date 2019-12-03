/** 普通線段樹，為了加速打字時間，所以只支援 1-based。 **/
/**
 * 把 df 設為:
 *   0     for 區間和/gcd/bit-or/bit-xor
 *   1     for 區間積/lcm
 *   9e18  for 區間最小值
 *   -9e18 for 區間最大值
 *   -1    for 區間 bit-and
 */
const ll df = 0;
const int N = ? ;  // maxn
#define ls i << 1  // 加速打字
#define rs i << 1 | 1
struct SegmentTree {
    ll a[N << 2];
    inline ll cal(ll a, ll b) {
        /**
         * 把回傳值設為對應的操作，例如 a+b 為區間和，還有像是
         * a*b, min(a,b), max(a,b), gcd(a,b), lcm(a,b),
         * a|b, a&b, a^b 等等。 */
        return a + b;
    }
    // 單點設值。外部呼叫的時候後三個參數不用填。注意只支援
    // 1-based ！
    ll set(int q, ll v, int i = 1, int l = 1, int r = N) {
        if (r < q || l > q) return a[i];
        if (l == r) return a[i] = v;
        int m = (l + r) >> 1;
        ll lo = set(q, v, ls, l, m);
        ll ro = set(q, v, rs, m + 1, r);
        return a[i] = cal(lo, ro);
    }
    // 查詢區間 [l, r] 總和
    // (或極值等等，看你怎麼寫)。外部呼叫的時
    // 候後三個參數不用填。注意只支援 1-based ！
    ll query(int ql, int qr, int i = 1, int l = 1,
             int r = N) {
        if (r < ql || l > qr) return df;
        if (ql <= l && r <= qr) return a[i];
        int m = (l + r) >> 1;
        ll lo = query(ql, qr, ls, l, m);
        ll ro = query(ql, qr, rs, m + 1, r);
        return cal(lo, ro);
    }
    // 建立 size = N 的空線段樹，所有元素都是 0 。注意只支援
    // 1-based ！
    SegmentTree() { memset(a, 0, sizeof(a)); }
};
