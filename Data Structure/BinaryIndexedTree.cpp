struct BIT {
    int N;
    vector<ll> bitarray;
    // Constructs a Binary Indexed Tree where n is size of array.
    BIT(int n) : N(n) { bitarray.assign(N + 1, 0); }
    ll query(int index) {
        index++;
        ll ret = 0;
        while (index > 0) ret += bitarray[index], index -= index & -index;
        return ret;
    }
    // Increases element at index by val, where index in [0, n).
    void add(int index, ll val) {
        index++;
        while (index <= N) bitarray[index] += val, index += index & -index;
    }
    // Queries sum in [left_inc, right_inc], where left_inc and right_inc in [0, n).
    ll query(int left_inc, int right_inc) { return query(right_inc) - query(left_inc - 1); }
};