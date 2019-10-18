// Queries phi(x) value. That is, the count of number which
// is coprime to and less than x.
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

// Queries all phi(x) values where x in [0, n).
vector<int> phi_in(int n) {
    vector<bool> p(n, 1);
    vector<int> r(n);
    p[0] = p[1] = 0;
    for (int i = 0; i < n; i++) r[i] = i;
    for (int i = 2; i < n; i++) {
        if (!p[i]) continue;
        r[i]--;
        for (int j = i * 2; j < n; j += i) {
            p[j] = 0;
            r[j] = r[j] / i * (i - 1);
        }
    }
    r[1] = 0;
    return r;
}
