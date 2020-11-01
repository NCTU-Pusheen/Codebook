ll fastpow(ll a, int p) { // a ^ p
    ll ret = 1;
    while (p) {
        if (p & 1) ret *= a;
        a *= a, p >>= 1;
    } return ret;
}
ll fastpow(ll a, ll p, ll m) { // (a ^ p) % m
    ll ret = 1;
    while (p) {
        if (p & 1) ret = ret * a % m;
        a = a * a % m, p >>= 1;
    } return ret;
}
