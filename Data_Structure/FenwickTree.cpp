#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/** 普通 BIT ，為了加速打字只支援 1-based **/
const int maxn = ? ;  // 開全域加速打字
struct BIT {
    vector<ll> a = vector<ll>(maxn);
    ll sum(int i) {
        ll r = 0; while (i > 0) r += a[i], i -= i & -i;
        return r;
    }
    // size = maxn 的空 BIT ，所有元素都是零
    BIT() {}
    // 注意 1-based
    void add(int i, ll v) {
        while (i <= maxn) a[i] += v, i += i & -i;
    }
    // 注意 1-based
    ll sum(int l, int r) { return sum(r) - sum(l - 1); }
};

/** 區間加值 BIT，只支援 1-based。複雜度 O(Q*log(N)) **/
const int maxn = ? ;  // 開全域加速打字
struct RangeUpdateBIT {
    vector<ll> d = vector<ll>(maxn), dd = vector<ll>(maxn);
    ll sum(int i) {
        ll s = 0, ss = 0;
        int c = i + 1;  // 這行不是打錯！要加！
        while (i > 0) s += d[i], ss += dd[i], i -= i & -i;
        return c * s - ss;
    }
    void add(int i, ll v) {
        int c = i;
        while (i <= maxn)
            d[i] += v, dd[i] += c * v, i += i & -i;
    }
    // 空 BIT，size = maxn，所有元素都是零，注意 1-based
    RangeUpdateBIT() {}
    // 必區間區間求和，注意 1-based
    ll sum(int l, int r) { return sum(r) - sum(l - 1); }
    // 必區間區間加值，注意 1-based
    void add(int l, int r, ll v) {
        add(l, v), add(r + 1, -v); }
};
