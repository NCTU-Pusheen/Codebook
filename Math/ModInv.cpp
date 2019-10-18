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
