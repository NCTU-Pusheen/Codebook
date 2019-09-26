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
/**
 * Support single element setting and range sum/min/max/product/gcd/lcm/etc query.
 *
 * Time Complexity: O(QlogN)
 * Space Complexity: O(N)
 */
class SegmentTree {
   private:
    /**
     * Set DF to:
     *   0    for sum/gcd query
     *   1    for product/lcm query
     *   inf  for min query
     *   -inf for max query
     */
    static const int DF = 0;
    vector<ll> a;
    int n;

    inline ll cal(int a, int b) {
        /**
         * Replace with:
         *   a + b      for sum query
         *   a * b      for product query
         *   gcd(a, b)  for gcd query
         *   lcm(a, b)  for lcm query
         *   min(a, b)  for min query
         *   max(a, b)  for max query
         */
        return a + b;
    }

    ll set(int i, int curl, int curr, int tar, ll v) {
        if (curr < tar || curl > tar) return a[i];
        if (curl == curr) return a[i] = v;
        int m = (curl + curr) / 2;
        ll l = set(i * 2 + 1, curl, m, tar, v);
        ll r = set(i * 2 + 2, m + 1, curr, tar, v);
        return a[i] = cal(l, r);
    }
    ll query(int i, int curl, int curr, int tarl, int tarr) {
        if (curr < tarl || curl > tarr) return DF;
        if (tarl <= curl && curr <= tarr) return a[i];
        int m = (curl + curr) / 2;
        ll l = query(i * 2 + 1, curl, m, tarl, tarr);
        ll r = query(i * 2 + 2, m + 1, curr, tarl, tarr);
        return cal(l, r);
    }

   public:
    // Constructs an empty segment tree with all values 0; n represeting count of elements
    SegmentTree(int n) : n(n) { a.assign(n * 4, DF); }
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
};

