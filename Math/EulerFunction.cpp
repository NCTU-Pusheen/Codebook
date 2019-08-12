// Queries phi(x) value.
int phi(int x) {
    int ret = x;
    for (int p = 2; p * p <= x; p++) {
        if (x % p == 0) {
            while (x % p == 0) x /= p;
            ret -= ret / p;
        }
    }
    if (x > 1) ret -= ret / x;
    return ret;
}

// Queries all phi(x) values where x in [0, n).
vector<int> phi_in(int n) {
    vector<bool> prime(n, 1);
    vector<int> ret(n);
    prime[0] = prime[1] = false;
    for (int i = 0; i < n; i++) ret[i] = i;
    for (int i = 2; i < n; i++) {
        if (!prime[i]) continue;
        ret[i]--;
        for (int j = i * 2; j < n; j += i) {
            prime[j] = false;
            ret[j] = ret[j] / i * (i - 1);
        }
    }
    ret[1] = 0;
    return ret;
}
