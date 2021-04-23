
// O(n) 求 1...n 對 p 的模逆元
ll precalc(int n, ll p){
    for(int i = 1; i <= n; i++){
        if(i == 1) inv[i] = 1;
        else inv[i] = (p - (p / i) * inv[p % i] % p) % p;
    }
}
