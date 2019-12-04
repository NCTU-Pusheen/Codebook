int order(ll b, ll p) {
    if (__gcd(b, p) != 1) return -1;
    int ret = 2;
    while (++ret)
        if (fastpow(b, ret, p) == 1) break;
    return ret;
}
// 把 fastpow 也抄過來，會用到。
// 問 (x^2 = y) mod p 的解。回傳 -1 表示 x 無解。
ll dsqrt(ll y, ll p) {
    if (__gcd(y, p) != 1) return -1;
    if (fastpow(y, (p - 1 / 2), p) == p - 1) return -1;
    int e = 0;
    ll s = p - 1;
    while (!(s & 1)) s >>= 1, e++;
    int q = 2;
    while (1)
        if (fastpow(q, (p - 1) / 2, p) == p - 1)
            break;
        else q++;
    ll x = fastpow(y, (s + 1) / 2, p);
    ll b = fastpow(y, s, p);
    ll g = fastpow(q, s, p);
    while (1) {
        int m;
        for (m = 0; m < e; m++) {
            int o = order(p, b);
            if (o == -1) return -1;
            if (o == fastpow(2, m, p)) break;
        }
        if (m == 0) return x;
        x = x * fastpow(g, fastpow(2, e - m - 1), p) % p;
        g = fastpow(g, fastpow(2, e - m, p), p);
        b = b * g % p;
        if (b == 1) return x;
        e = m;
    }
}
