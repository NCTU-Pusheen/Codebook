struct FenwickTree {
    const int N;
    vector<ll> d, dd;
    // Constructs a Fenwick Tree where n is size of array.
    FenwickTree(int n) : N(n) {
        d.assign(N + 2, 0);
        dd.assign(N + 2, 0);
    }
    ll query(int index) {
        index++;
        ll s = 0, ss = 0;
        ll c = index + 1;
        while (index > 0) {
            s += d[index], ss += dd[index];
            index -= index & -index;
        }
        return c * s - ss;
    }
    void add(int index, ll val) {
        index++;
        int c = index;
        while (index <= N) {
            d[index] += val, dd[index] += c * val;
            index += index & -index;
        }
    }
    // Queries sum in [left_inc, right_inc], where left_inc and right_inc in [0, n).
    ll query(int left_inc, int right_inc) { return query(right_inc) - query(left_inc - 1); }
    // Increases all elements in [left_inc, right_inc] by val, where left_inc and right_inc in [0, n).
    void add(int left_inc, int right_inc, ll val) { add(left_inc, val), add(right_inc + 1, -val); }
};