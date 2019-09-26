#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
const double PI = acos(-1);
#define x first
#define y second
#define iter(c) c.begin(), c.end()
#define ms(a) memset(a, 0, sizeof(a))
#define mss(a) memset(a, -1, sizeof(a))
#define mp(e, f) make_pair(e, f)

// A binary indexed tree supports increasing (but not directly setting) specific value and querying range sum.
// Time Complexity: O(NlogN)
class BIT {
   private:
    int n;
    vector<ll> a;

    ll sum(int i) {
        i++;
        ll r = 0;
        while (i > 0) r += a[i], i -= i & -i;
        return r;
    }

   public:
    // Constructs an binary indexed tree with all values initialized to 0, where n is size of array.
    BIT(int n) : n(n) { a.resize(n + 1); }
    // Increases element at i by v, where i in [1, n].
    void add(int i, ll v) {
        i++;
        while (i <= n) a[i] += v, i += i & -i;
    }
    // Queries sum in [l, r], where l and r in [1, n].
    ll sum(int l, int r) { return sum(r) - sum(l - 1); }
};

// A Fenwick Tree supports increasing (but not directle setting) range values and querying range sum.
// Time Complexity: (NlogN)
// SUPPORT RANGE INCREASING
class FenwickTree {
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
    FenwickTree(int n) : n(n) {
        d.resize(n + 2);
        dd.resize(n + 2);
    }
    // Queries sum in [l, r], where l and r in [1, n].
    ll sum(int l, int r) { return sum(r) - sum(l - 1); }
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
    // Constructs an empty segment tree with all values 0; n represeting count of elements
    SegmentTree(int n) : n(n) { a.resize(n * 4); }
    // Sets element located at index i to value v, where i in [1, n]
    void set(int i, ll v) {
        i--;  // comment this line to 0-based
        set(0, 0, n - 1, i, v);
    }
    // Queries range sum/min/max/gcd etc, whre l and r in [1, n]
    ll query(int l, int r) {
        l--, r--;  // comment this line to 0-based
        return query(0, 0, n - 1, l, r);
    }

    // If you want to quickly initialized a segment tree, adds following code.
   public:
    // Constructs a segment tree with initialized data, whose index starts at 1; n indicating size of data
    SegmentTree(const vector<ll>& data, int n) : n(n) {
        a.resize(n * 4);
        init(data, 0, 0, n - 1);
    }

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

// A 2D BIT supports increasing single value and range sum.
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
    // Increases element at location (x,y) by value v, where x in [1, r] and y in [1, c]
    void add(int x, int y, ll v) {
        x++;
        while (x <= r) a[x].add(y, v), x += x & -x;
    }
    // Queries sum of matrix from [x0,y0] to [x1,y1] where x in [1, r] and y in [1, c]
    ll sum(int x0, int y0, int x1, int y1) { return sum(x1, y1) - sum(x0 - 1, y1) - sum(x1, y0 - 1) + sum(x0 - 1, y0 - 1); }
};

// A RangeUpdateSegmentTree supports range updating and single element access.
class RangeUpdateSegmentTree {
   private:
    vector<bool> u;
    vector<ll> a;
    int n;

    void range_set(int i, int curl, int curr, int tarl, int tarr, int v) {
        if (curl > tarr || curr < tarl) return;
        if (tarl <= curl && curr <= tarr && u[i]) {
            a[i] = v;
            return;
        }
        if (u[i]) {
            u[i * 2 + 1] = u[i * 2 + 2] = 1;
            a[i * 2 + 1] = a[i * 2 + 2] = a[i];
        }

        u[i] = 0;
        int m = (curl + curr) / 2;
        range_set(i * 2 + 1, curl, m, tarl, tarr, v);
        range_set(i * 2 + 2, m + 1, curr, tarl, tarr, v);
        if (u[i * 2 + 1] && u[i * 2 + 2]) {
            u[i] = 1;
            a[i] = a[i * 2 + 1] + a[i * 2 + 2];
        }
    }

    ll query(int i, int curl, int curr, int tar) {
        if (u[i]) return a[i];
        int m = (curl + curr) / 2;
        ll l = query(i * 2 + 1, curl, m, tar);
        ll r = query(i * 2 + 2, m + 1, curr, tar);
        return l + r;
    }

   public:
    // Constructs a segment tree with size n and all elements initialized to 0
    RangeUpdateSegmentTree(int n) : n(n) {
        a.resize(4 * n);
        u.resize(4 * n);
        u[0] = 1;
    }

    // Sets all elements in range [l, r] to value v, where l, r in [1, n]
    void range_set(int l, int r, int v) {
        l--, r--;  // comment this line to 0-based
        range_set(0, 0, n - 1, l, r, v);
    }

    // Queries an element by index
    ll query(int i) {
        i--;  // comment this line to 0-based
        query(0, 0, n - 1, i);
    }
};