// Queires the first index where sub appears in str; -1 indicates no matching.
int rollhash(string& str, string& sub) {
    const int X = 1e6 + 99, MOD = 1e9 + 9;
    ll xx = 1;
    for (int i = 0; i < sub.size(); i++) xx = xx * X % MOD;
    ll subhash = 0;
    for (char c : sub) subhash = (subhash * X + c) % MOD;

    vector<ll> hash = {0};
    for (int i = 0; i < str.size(); i++) {
        hash.push_back((hash.back() * X + str[i]) % MOD);
        if (i >= sub.size()) {
            ll h = (hash.back() - hash[i - sub.size() + 1] * xx % MOD + MOD) % MOD;
            if (h == subhash) return i - sub.size() + 1;
        }
    }
    return -1;
}
