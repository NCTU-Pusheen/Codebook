// 查詢 phi(x) 亦即比 x 小且與 x 互質的數的數量。
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
// 查詢所有 phi(x) ，且 x in [0, n) 。注意右開區間，回傳陣列。
vector<int> phi_in(int n) {
    vector<bool> p(n, 1); vector<int> r(n);
    p[0] = p[1] = 0;
    for (int i = 0; i < n; i++) r[i] = i;
    for (int i = 2; i < n; i++) {
        if (!p[i]) continue;
        r[i]--;
        for (int j = i * 2; j < n; j += i)
            p[j] = 0, r[j] = r[j] / i * (i - 1);
    }
    r[1] = 0;
    return r;
}
