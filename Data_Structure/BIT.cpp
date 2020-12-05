// 區間加值 BIT 只支援 1-based ，左閉右閉
namespace RangeUpdateBIT { // O(log N)
ll d[N], dd[N];
ll sum(int i) {
    ll s = 0, ss = 0;
    int c = i + 1;
    while (i > 0) s += d[i], ss += dd[i], i -= i & -i;
    return c * s - ss;
}
void add(int i, ll val) { // O(log N)
    int c = i;
    while (i < N)
        d[i] += val, dd[i] += c * val, i += i & -i;
}
void add (int l, int r, ll val) {
    if (!l) l++;
    add(l, val), add(r + 1, -val);
}
}  // namespace RangeUpdateBIT

// 1-based only，左閉右閉
namespace RangeUpdateBit2D {

ll d[N][N];
ll sum(int x, int y) { // sum in range [1:x][1:y], O(log^2 N)
    if(!x || !y) return 0;
    ll ret = 0;
    for (int i = x; i; i -= i & -i)
        for (int j = y; j; j -= j & -j)
            ret += d[i][j];
    return ret;
}
void add(int x, int y, ll val) { // add at [x][y], O(log^2 N)
    for (int i = x; i < N; i += i & -i)
        for (int j = y; j < N; j += j & -j)
            d[i][j] += val;
}
}  // namespace RangeUpdateBit2D
