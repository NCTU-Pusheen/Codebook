// Queries (a ^ p) mod m.
ll dpow(ll a, ll p, ll m) {
    ll ret = 1;
    while (p) {
        if (p & 1) ret = ret * a % m;
        a = a * a % m, p >>= 1;
    }
    return ret;
}

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

// Queries value x such that (ax == 1) mod p, where p is
// prime and a is positive.
ll modinv(ll a, ll p) {
    if (p == 1) return 0;
    ll pp = p, y = 0, x = 1;
    while (a > 1) {
        ll q = a / p, t = p;
        p = a % p, a = t, t = y, y = x - q * y, x = t;
    }
    if (x < 0) x += pp;
    return x;
}

// Queries value x such that (ax == b) mod p, where p is
// prime and a, b are positive.
ll modinv(ll a, ll b, ll p) {
    ll ret = modinv(a, p);
    return ret * b % p;
}
