// A binary indexed tree supports increasing (but not directly setting) specific value and querying range sum.
// Time Complexity: O(NlogN)
// SIMPLEST ONE
class BIT {
   private:
    int n;
    vector<ll> a;

    ll query(int i) {
        i++;
        ll r = 0;
        while (i > 0) r += a[i], i -= i & -i;
        return r;
    }

   public:
    // Constructs an empty binary indexed tree where n is size of array.
    BIT(int n) : n(n) { a.resize(n + 1); }
    // Increases element at i by v, where i in [1, n].
    void add(int i, ll v) {
        i++;
        while (i <= n) a[i] += v, i += i & -i;
    }
    // Queries sum in [l, r], where l and r in [1, n].
    ll query(int l, int r) { return query(r) - query(l - 1); }
};

// A Fenwick Tree supports increasing (but not directle setting) range values and querying range sum.
// Time Complexity: (NlogN)
// SUPPORT RANGE INCREASING
class FenwickTree {
   private:
    int n;
    vector<ll> d, dd;

    ll query(int i) {
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
    FenwickTree(int n) : n(n) {
        d.resize(n + 2);
        dd.resize(n + 2);
    }
    // Queries sum in [l, r], where l and r in [1, n].
    ll query(int l, int r) { return query(r) - query(l - 1); }
    // Increases all elements in [l, r] by v, where l and r in [1, n].
    void add(int l, int r, ll v) { add(l, v), add(r + 1, -v); }
};

// A segment tree supports directly setting spcific value and querying range sum, min, max, product, gcd, lcm,
// Time Complexity: (NlogN)
// SUPPORT MANY TYPE OF QUERIES
class SegmentTree {
   private:
    vector<ll> a;
    int n;

   private:
    ll set(int i, int curl, int curr, int tar, ll v) {
        if (curr < tar || curl > tar) return a[i];
        if (curl == curr) return a[i] = v;
        int m = (curl + curr) / 2;
        ll l = set(i * 2 + 1, curl, m, tar, v);
        ll r = set(i * 2 + 2, m + 1, curr, tar, v);
        return a[i] = l + r;  // for sum query; replace with min(l,r), gcd(l,r), etc for other queries
    }
    ll query(int i, int curl, int curr, int tarl, int tarr) {
        if (curr < tarl || curl > tarr) return 0;  // for sum, gcd query; replace with 1/INT_MAX/INT_MIN for product/min/max query
        if (tarl <= curl && curr <= tarr) return a[i];
        int m = (curl + curr) / 2;
        ll l = query(i * 2 + 1, curl, m, tarl, tarr);
        ll r = query(i * 2 + 2, m + 1, curr, tarl, tarr);
        return l + r;  // for sum query; replace with min(l,r), gcd(l,r), etc for other queries
    }

   public:
    // Constructs an empty segment tree with all values 0; n represeting size of elements
    SegmentTree(int n) : n(n) { a.resize(n * 4); }
    // Constructs a segment tree with initialized data, whose index starts at 1; n indicating size of data
    SegmentTree(const vector<ll>& data, int n) : n(n) {
        a.resize(n * 4);
        init(data, 0, 0, n - 1);
    }
    // Sets element located at index i to value v, where i in [1, n]
    void set(int i, ll v) {
        i--;  // comment this line to 0-based
        set(0, 0, n - 1, i, v);
    }
    // Queries range sum/min/max/gcd etc, whre l and r in [1, N]
    ll query(int l, int r) {
        l--, r--;  // comment this line to 0-based
        return query(0, 0, n - 1, l, r);
    }

    // BELOWING CODES ARE OMITTABLE FOR EMPTY SEGMENT TREE
   private:
    ll init(const vector<ll>& data, int i, int curl, int curr) {
        if (curl == curr) {
            if (curl >= n)
                return a[i] = 0;
            else {
                curl++;  // comment this line to 0-based
                return a[i] = data[curl];
            }
        }
        int m = (curl + curr) / 2;
        ll l = init(data, i * 2 + 1, curl, m);
        ll r = init(data, i * 2 + 2, m + 1, curr);
        return a[i] = l + r;  // for sum query; replace with min(l,r), gcd(l,r), etc for other queries
    }
};