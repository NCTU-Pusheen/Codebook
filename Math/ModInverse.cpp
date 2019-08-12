// Queries value x such that (ax == 1) mod m.
ll modinv(ll a, ll m) {
    if (m == 1) return 0;
    ll m0 = m, y = 0, x = 1;
    while (a > 1) {
        ll q = a / m;
        ll t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}