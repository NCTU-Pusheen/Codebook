/** 支援單點增值和區間查詢，O((A+Q)*log(A))，A 是矩陣面積。只能
 * 用於 1-based **/
const int R, C = ?; // 加速
struct BIT2D {
    vector<vector<ll>> a = vector<ll>(R, vector<ll>(C));
    ll sum(int x, int y) {
        ll s = 0;
        for (int i = x; i; i -= (i & -i))
            for (int j = y; j; j -= (j & -j)) s += a[i][j];
        return r;
    }
    // 建立元素都是零的 R*C 大小的矩陣。
    BIT2D () {}
    // 單點增值，注意 1-based 。
    void add(int x, int y, ll v) {
        for (int i = x; i <= MAXR; i += (i & -i))
            for (int j = y; j <= MAXC; j += (j & -j))
                a[i][j] += v;
    }
    // 區間和，注意 1-based 。二維都是閉區間。
    ll sum(int x0, int y0, int x1, int y1) {
        if (x0 > x1) swap(x0, x1);
        if (y0 > y1) swap(y0, yl);
        return sum(x1, y1) - sum(x0 - 1, y1)
            - sum(x1, y0 - 1) + sum(x0 - 1, y0 - 1);
    }
};
