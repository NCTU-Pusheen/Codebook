/** 支援單點增值和區間查詢，O((A+Q)*log(A))，A
 * 是矩陣面積。只能 用於 1-based **/
const int R = 256, C = 256;
class BIT2D {
   private:
    ll a[R + 1][C + 1];
    ll sum(int x, int y) {
        ll ret = 0;
        for (int i = x; i; i -= (i & -i))
            for (int j = y; j; j -= (j & -j))
                ret += a[i][j];
        return ret;
    }
   public:
    // 建立元素都是零的 R*C 大小的矩陣。
    BIT2D() { memset(a, 0, sizeof(a)); }
    // 單點增值，注意 1-based 。
    void add(int x, int y, ll v) {
        for (int i = x; i <= R; i += (i & -i))
            for (int j = y; j <= C; j += (j & -j))
                a[i][j] += v;
    }
    // 區間和，注意 1-based 。二維都是閉區間。
    ll sum(int x0, int y0, int x1, int y1) {
        return sum(x1, y1) - sum(x0 - 1, y1) -
               sum(x1, y0 - 1) + sum(x0 - 1, y0 - 1);
    }
};
