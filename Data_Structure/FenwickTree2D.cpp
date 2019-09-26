/**
 * Support single elememt increment and range sum query in 2D.
 *
 * Time Complexity: O(?)
 * Space Complexity: O(RC)
 */
class BIT2D {
   private:
    int r, c;
    vector<BIT> a;

    ll sum(int x, int y) {
        x++;
        ll r = 0;
        while (x > 0) r += a[x].sum(1, y), x -= x & -x;
        return r;
    }

   public:
    // Constructs a 2D BIT with all value initialized to 0; r/c is count of rows/column of matrix
    BIT2D(int r, int c) : r(r), c(c) { a.assign(r + 1, BIT(c)); }
    // Increases element at coordinates (x, y) by value v, where x in [1, r] and y in [1, c]
    void add(int x, int y, ll v) {
        x++;
        while (x <= r) a[x].add(y, v), x += x & -x;
    }
    // Queries sum of matrix from (x0, y0) (inclusive) to (x1, y1) (inclusive), where x in [1, r] and y in [1, c]
    ll sum(int x0, int y0, int x1, int y1) { return sum(x1, y1) - sum(x0 - 1, y1) - sum(x1, y0 - 1) + sum(x0 - 1, y0 - 1); }
};