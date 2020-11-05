const double PI = acos(-1);
typedef complex<double> C;
namespace FFT {

void bit_reverse(vector<C>& v) {
    int n = v.size();
    for (int i = 1, j = n / 2; i < n - 1; i++) {
        if (i < j) swap(v[i], v[j]);
        int k = n / 2;
        while (j >= k) j -= k, k /= 2;
        if (j < k) j += k;
    }
}

// Given a function whose co-efficient is v, calculates its FFT and stores
// resulting co-efficients in local. Length of v MUST be 2^N.
void fft(vector<C>& v, bool is_inverse = false) {
    int n = v.size(), len = __lg(n), f = is_inverse ? -1 : 1;
    assert(n == (1 << len));
    bit_reverse(v);
    for (int k = 2; k <= n; k <<= 1) {
        int m = k >> 1;
        for (int i = 0; i < m; i++) {
            C c = {0, i * f * PI / m};
            auto w = exp(c);
            for (int j = i; j < n; j += k) {
                int k = j + m;
                C s = v[j], t = w * v[k];
                v[j] = s + t, v[k] = s - t;
            }
        }
    }
    if (is_inverse)
        for (int i = 0; i < n; ++i) v[i] /= n;
}

};  // namespace FFT