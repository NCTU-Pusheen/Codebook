// 給 a,b ，解 ax+by=gcd(a,b)
typedef pair<ll, ll> pii;
pii extgcd(ll a, ll b) {
    if (b == 0) return {1, 0};
    ll k = a / b;
    pii p = extgcd(b, a - k * b);
    return {p.second, p.first - k * p.second};
}
