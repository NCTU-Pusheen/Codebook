struct SparseTable {
    const int N;
    vector<vector<ll>> bitarray;
    // Constructs a sparse table with size same as vec.
    SparseTable(const vector<ll>& vec) : N(vec.size()) {
        bitarray.assign(__lg(N) + 1, vector<ll>(N));
        bitarray[0] = vec;
        for (int i = 1; (1 << i) <= N; i++) {
            int k = N - (1 << i);
            for (int j = 0; j < k; j++) {
                // Comparator may be needed.
                bitarray[i][j] = max(bitarray[i - 1][j], bitarray[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    // Queries the maximum element in [left_inc, right_inc] where left_inc and right_inc in [0, n).
    ll query(int left_inc, int right_inc) {
        int k = __lg(right_inc - left_inc + 1);
        return max(bitarray[k][left_inc], bitarray[k][right_inc - (1 << k) + 1]);
    }
};