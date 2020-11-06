// int(complex.real() + 0.05)   // .imag()
template <typename T, typename VT = vector<complex<T>>>
struct FFT {
    const T pi;
    FFT(const T pi = acos((T)-1.0)) : pi(pi) {}
    unsigned bit_reverse (unsigned a, int len) {
        a = ((a&0x55555555U)<<1)  | ((a&0xAAAAAAAAU)>>1);
        a = ((a&0x33333333U)<<2)  | ((a&0xCCCCCCCCU)>>2);
        a = ((a&0x0F0F0F0FU)<<4)  | ((a&0xF0F0F0F0U)>>4);
        a = ((a&0x00FF00FFU)<<8)  | ((a&0xFF00FF00U)>>8);
        a = ((a&0x0000FFFFU)<<16) | ((a&0xFFFF0000U)>>16);
        return a >> (32-len);
    }
    void fft (bool is_inv, VT &in, VT &out, int N) {
        int bitlen = __lg(N), num = is_inv ? -1 : 1;
        for(int i = 0; i < N; ++i)
            out[bit_reverse(i, bitlen)] = in[i];
        for(int step = 2, mh = 1; step <= N; step <<= 1, mh <<= 1){
            for(int i = 0; i < mh; ++i){
                complex<T> wi = exp(complex<T>(0, i * num * pi / mh));
                for(int j = i, k = i + mh; j < N; j += step, k += step) {
                    complex<T> u = out[j], t = wi * out[k];
                    out[j] = u + t, out[k] = u - t;
                }
            }
        }
        for (int i = 0; is_inv && i < N; ++i)
            out[i] /= N;
    }
};
int main () { // polynomial multiplication
	FFT<double> F; int n = 4;
	vector<complex<double>> a = {1, 2, 0, 0};
	vector<complex<double>> b = {2, 3, 0, 0};
	vector<complex<double>> a_fft(n), b_fft(n), ab_fft(n), ab(n);
	F.fft(0, a, a_fft, 4), F.fft(0, b, b_fft, 4);
	for (int i = 0; i < n; i++)
		ab_fft[i] = a_fft[i] * b_fft[i];
	F.fft(1, ab_fft, ab, n);
	for (auto p : ab)
		cout << int(p.real() + 1e-6) << " ";
	return 0;
}
