const int N = 1e5;
int np[N], mu[N]; // 結果存在 mu


np[1] = mu[1] = 1;
vector<int> primes;
for (int i = 2; i < N; i++) {
    if (!np[i]) mu[i] = -1, primes.push_back(i);
    for (auto& p : primes) {
        if (i * p > N) break;
        np[i * p] = 1;
        if (i % p == 0) {
            mu[i * p] = 0;
            break;
        }
        mu[i * p] = -mu[i];
    }
}