// 問 sub 在 str 第一次出現的開頭 index 。-1 表示找不到。
int rollhash(string& str, string& pat) {
    const int x = 1e6 + 99, m = 1e9 + 9; // 隨意大質數
    ll xx = 1, sh = 0;
    for (int i = 0; i < pat.size(); i++) xx = xx * x % m;
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
