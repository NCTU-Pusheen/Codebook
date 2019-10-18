// Helper function for dsqrt
int order(ll b, ll p) {
    if (__gcd(b, p) != 1) return -1;
    int ret = 2;
    while (++ret)
        if (dpow(b, ret, p) == 1) break;
    return ret;
}

// Queries x where (x^2 = y) mod p. Returns -1 if no such x.
ll dsqrt(ll y, ll p) {
    if (__gcd(y, p) != 1) return -1;
    if (dpow(y, (p - 1 / 2), p) == p - 1) return -1;

    int e = 0;
    ll s = p - 1;
    while (!(s & 1)) s >>= 1, e++;

    int q = 2;
    while (1)
        if (dpow(q, (p - 1) / 2, p) == p - 1)
            break;
        else
            q++;

    ll x = dpow(y, (s + 1) / 2, p);
    ll b = dpow(y, s, p);
    ll g = dpow(q, s, p);

    while (1) {
        int m;
        for (m = 0; m < e; m++) {
            int o = order(p, b);
            if (o == -1) return -1;
            if (o == dpow(2, m, p)) break;
        }
        if (m == 0) return x;

        x = x * dpow(g, dpow(2, e - m - 1), p) % p;
        g = dpow(g, dpow(2, e - m, p), p);
        b = b * g % p;
        if (b == 1) return x;
        e = m;
    }
}
