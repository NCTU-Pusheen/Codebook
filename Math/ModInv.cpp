int phi(int x) {
    int r = x;
    for (int p = 2; p * p <= x; p++) {
        if (x % p == 0) {
            while (x % p == 0) x /= p;
            r -= r / p;
        }
    }
    if (x > 1) r -= r / x;
    return r;
}
// 解 (ax == 1) mod b。a、b 互質整數，否則不存在modinv。
ll modinv(ll a, ll b){
	if(__gcd(a, b) != 1) return -1;
	// Euler 定理: a^phi(b) == 1 (mod b)
	// -> a^(phi(b) - 1) is the mod inverse to b of a
	int mod_inv_pow = phi(b) - 1;
	int ans = 1, base = a % b;
	while(mod_inv_pow > 0){
		if(mod_inv_pow & 1)
			ans = ans * base % b;
		base = base * base % b;
		mod_inv_pow >>= 1;
	} return ans;
}
ll modinv(ll a, ll p) { //(ax == 1)mod p，p質數，a正整數
    if (p == 1) return 0;
    ll pp = p, y = 0, x = 1;
    while (a > 1) {
        ll q = a / p, t = p;
        p = a % p, a = t, t = y, y = x - q * y, x = t;
    }
    if (x < 0) x += pp;
    return x;
}
// 解 (ax == b) mod p 。p 必須是質數，a 和 b 是正整數。
ll modinv(ll a, ll b, ll p) {
    ll ret = modinv(a, p);
    return ret * b % p;
}
