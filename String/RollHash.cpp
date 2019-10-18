/**
 * Queires the first index where pat appears in str; -1
 * indicates no matching.
 */
int rollhash(string& str, string& pat) {
    const int x = 1e6 + 99, m = 1e9 + 9;
    ll xx = 1;
    for (int i = 0; i < pat.size(); i++) xx = xx * x % m;
    ll sh = 0;
    for (char c : pat) sh = (sh * x + c) % m;

    vector<ll> hash = {0};
    for (int i = 0; i < str.size(); i++) {
        hash.push_back((hash.back() * x + str[i]) % m);
        if (i < pat.size()) continue;
        ll h = hash.back() - hash[i - pat.size() + 1] * xx;
        h = (h % m + m) % m;
        if (h == sh) return i - pat.size() + 1;
    }
    return -1;
}
