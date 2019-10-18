// Queries a ^ p.
ll fastpow(ll a, int p) {
    ll ret = 1;
    while (p) {
        if (p & 1) ret *= a;
        a *= a, p >>= 1;
    }
    return ret;
}

