/**
 * Support single element increment and range sum query.
 *
 * Time Complexity: O(QlogN)
 * Space Complexity: O(N)
 */
class BIT {
   private:
    int n;
    vector<ll> a;

    ll sum(int i) {
        i++;
        ll r = 0;
        while (i > 0) assert(0 <= i && i < a.size()), r += a[i], i -= i & -i;
        return r;
    }

   public:
    // Constructs an binary indexed tree with all values initialized to 0, where n is size of array.
    BIT(int n) : n(n) { a.resize(n + 1); }
    // Increases element at index i by value v.
    void add(int i, ll v) {
        i--;  // comment this line to 0-based
        i++;
        while (i <= n) assert(0 <= i && i < a.size()), a[i] += v, i += i & -i;
    }
    // Queries sum in [l, r].
    ll sum(int l, int r) {
        l--, r--;  // comment this line to 0-based
        return sum(r) - sum(l - 1);
    }
};

/**
 * Support range elements increment and range sum query.
 *
 * Time Complexity: (QlogN)
 * Space Complexity: O(N)
 */
class RangeUpdateBIT {
   private:
    int n;
    vector<ll> d, dd;

    ll sum(int i) {
        i++;
        ll s = 0, ss = 0;
        int c = i + 1;
        while (i > 0) {
            s += d[i], ss += dd[i];
            i -= i & -i;
        }
        return c * s - ss;
    }
    void add(int i, ll v) {
        i++;
        int c = i;
        while (i <= n) {
            d[i] += v, dd[i] += c * v;
            i += i & -i;
        }
    }

   public:
    // Constructs an empty Fenwick Tree where n is size of array.
    RangeUpdateBIT(int n) : n(n) {
        d.resize(n + 1);
        dd.resize(n + 1);
    }
    // Queries sum in [l, r].
    ll sum(int l, int r) {
        l--, r--;  // comment this line to 0-based
        return sum(r) - sum(l - 1);
    }
    // Increases all elements in [l, r] by value v.
    void add(int l, int r, ll v) {
        l--, r--;  // comment this line to 0-based
        add(l, v), add(r + 1, -v);
    }
};