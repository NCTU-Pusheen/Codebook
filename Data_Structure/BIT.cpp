// 區間加值 BIT 只支援 1-based ，左閉右閉
namespace RangeUpdateBIT { // O(log N)
ll d[maxn], dd[maxn];
ll sum(int i) {
    ll s = 0, ss = 0;
    int c = i + 1;
    while (i > 0) s += d[i], ss += dd[i], i -= i & -i;
    return c * s - ss;
}
void add(int i, ll v) { // O(log N)
    int c = i;
    while (i < maxn)
        d[i] += v, dd[i] += c * v, i += i & -i;
}
}  // namespace RangeUpdateBIT

// 1-based only，左閉右閉
namespace RangeUpdateBit2D {

ll d[N][N];
ll sum(int x, int y) {  // O(log^2 N)
    ll ret = 0;
    for (int i = x; i; i -= i & -i)
        for (int j = y; j; j -= j & -j)
            ret += d[i][j];
    return ret;
}
void add(int x, int y, ll val) {  // O(log^2 N)
    for (int i = x; i < N; i += i & -i)
        for (int j = y; j < N; j += j & -j)
            d[i][j] += val;
}
}  // namespace RangeUpdateBit2D
