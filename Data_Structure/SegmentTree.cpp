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
const int maxn = ?;      // 開全域加速打字
#define ls i << 1        // 加速打字
#define rs i << 1 | 1
struct SegmentTree {
    vector<ll> a = vector<ll>(maxn);
    inline ll cal(ll a, ll b) {
        /**
         * 把回傳值設為對應的操作，例如 a+b 為區間和，還有像是
         * a*b, min(a,b), max(a,b), gcd(a,b), lcm(a,b),
         * a|b, a&b, a^b 等等。
         */
        return a + b;
    }
    // 單點設值。外部呼叫的時候後三個參數不用填。注意只支援 1-based ！
    ll set(int q, ll v, int i = 1, int l = 1, int r = maxn)
    {
        if (r < q || l > q) return a[i];
        if (l == r) return a[i] = v;
        int m = (l + r) >> 1;
        ll rl = set(q, v, ls, l, m);
        ll rr = set(q, v, rs, m + 1, r);
        return a[i] = cal(rl, rr);
    }
    // 查詢區間 [l, r] 總和 (或極值等等，看你怎麼寫)。外部呼叫的時
    // 候後三個參數不用填。注意只支援 1-based ！
    ll query(int ql, int qr, int i = 1, int l = 1,
             int r = maxn) {
        if (r < ql || l > qr) return df;
        if (ql <= l && r <= qr) return a[i];
        int m = (l + r) >> 1;
        ll rl = query(ql, qr, ls, l, m);
        ll rr = query(ql, qr, rs, m + 1, r);
        return cal(rl, rr);
    }
    // 建立 size = maxn 的空線段樹，所有元素都是 0 。注意只支援
    // 1-based ！
    SegmentTree() {}
};
