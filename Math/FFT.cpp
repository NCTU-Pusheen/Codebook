typedef unsigned u;
typedef complex<double> c;
const double PI = acos(-1.0);
u bit_rev(u a, int len) {
    a = ((a & 0x55555555U) << 1)  | ((a & 0xAAAAAAAAU) >> 1);
    a = ((a & 0x33333333U) << 2)  | ((a & 0xCCCCCCCCU) >> 2);
    a = ((a & 0x0F0F0F0FU) << 4)  | ((a & 0xF0F0F0F0U) >> 4);
    a = ((a & 0x00FF00FFU) << 8)  | ((a & 0xFF00FF00U) >> 8);
    a = ((a & 0x0000FFFFU) << 16) | ((a & 0xFFFF0000U) >> 16);
    return a >> (32 - len);
}
vector<c> fft(vector<c>& in, bool is_inv) {
    int n = in.size();
    int bitlen = __lg(n), z = is_inv ? -1 : 1;
    vector<c> ret(n);
    for (int i = 0; i < n; i++) ret[bit_rev(i, bitlen)] = in[i];
    for (int s = 2, m = 1; s <= n; s <<= 1, m <<= 1) {
        for (int i = 0; i < m; i++) {
            c w = exp(c(0, i * z * PI / m));
            for (int j = i, k = i + m; j < n; j += s, k += s) {
                c u = ret[j], t = w * ret[k];
                ret[j] = u + t, ret[k] = u - t;
            }
        }
    }
    for (int i = 0; is_inv && i < n; i++) ret[i] /= n;
    return ret;
}
#define T double  // 或者用 long long
vector<T> poly_mul(vector<T>& arg1, vector<T>& arg2) { // 升冪
    int n = ? // 二的指數且大於等於 arg1.size() + arg2.size() - 1
    vector<c> a(arg1.begin(), arg1.end()), b(arg2.begin(), arg2.end()), abfft(n);
    a.resize(n, 0.0), b.resize(n, 0.0);
    auto afft = fft(a, 0), bfft = fft(b, 0);
    for (int i = 0; i < n; i++) abfft[i] = afft[i] * bfft[i];
    auto ab = fft(abfft, 1);
    vector<T> ret;
    for (auto val : ab) ret.push_back(val.real()); // 若是整數則四捨五入避免精度誤差
    // 回傳的陣列會有很多後綴零，自己視情況去掉
    return ret;
}