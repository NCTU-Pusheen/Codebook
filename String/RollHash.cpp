// 問 pat 在 str 第一次出現的開頭 index 。-1 表示找不到。
int rollhash(string& str, string& pat) {
    const ll x = 1e6 + 99;  // 隨意大質數，建議 1e6
    const ll m = 1e9 + 9;   // 隨意大質數，建議 1e9
    assert(pat.size());     // pat 不能是空字串
    ll xx = 1, sh = 0;
    for (char c : pat)
        sh = (sh * x + c) % m, xx = xx * x % m;
    deque<ll> hash = {0};
    int ret = 0;
    for (char c : str) {
        hash.push_back((hash.back() * x + c) % m);
        if (hash.size() <= pat.size()) continue;
        ll h = hash.back() - hash.front() * xx;
        h = (h % m + m) % m;
        if (h == sh) return ret;
        hash.pop_front();
        ret++;
    } return -1;
}
