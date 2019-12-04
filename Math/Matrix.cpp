struct Matrix {
    int r, c;
    vector<vector<ll>> m;
    Matrix(int r, int c): r(r), c(c), m(r, vector<ll>(c)) {}
    vector<ll> &operator[](int i) { return m[i]; }
    Matrix operator+(const Matrix &a) {
        Matrix rev(r, c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                rev[i][j] = m[i][j] + a.m[i][j];
        return rev;
    }
    Matrix operator-(const Matrix &a) {
        Matrix rev(r, c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                rev[i][j] = m[i][j] - a.m[i][j];
        return rev;
    }
    Matrix operator*(const Matrix &a) {
        Matrix rev(r, a.c);
        Matrix tmp(a.c, a.r);
        for (int i = 0; i < a.r; ++i)
            for (int j = 0; j < a.c; ++j)
                tmp[j][i] = a.m[i][j];
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < a.c; ++j)
                for (int k = 0; k < c; ++k)
                    rev.m[i][j] += m[i][k] * tmp[j][k];
        return rev;
    }
    // 回傳反矩陣。注意這是 const 方法所以原矩陣不受影響。
    Matrix inverse() const {
        Matrix t(r, r + c);
        for (int y = 0; y < r; y++) {
            t.m[y][c + y] = 1;
            for (int x = 0; x < c; x++) t.m[y][x] = m[y][x];
        }
        if (!t.gauss()) return Matrix(0, 0);
        Matrix ret(c, r);
        for (int y = 0; y < r; y++)
            for (int x = 0; x < c; x++)
                ret[y][x] = t.m[y][c + x] / t.m[y][y];
        return ret;
    }
    // 做高斯消去 (最高次係數應置於最左，常數應置於最右) 並回傳 det
    // 行列式值。複雜度 O(n^3)。如果不是方陣，回傳值無意義。
    ll gauss() {
        vector<ll> lazy(r, 1);
        bool sign = false;
        for (int i = 0; i < r; ++i) {
            if (m[i][i] == 0) {
                int j = i + 1;
                while (j < r && !m[j][i]) j++;
                if (j == r) continue;
                m[i].swap(m[j]); sign = !sign;
            }
            for (int j = 0; j < r; ++j) {
                if (i == j) continue;
                lazy[j] = lazy[j] * m[i][i];
                ll mx = m[j][i];
                for (int k = 0; k < c; ++k)
                    m[j][k] =
                        m[j][k] * m[i][i] - m[i][k] * mx;
            }
        }
        ll det = sign ? -1 : 1;
        for (int i = 0; i < r; ++i) {
            det = det * m[i][i] / lazy[i];
            for (auto &j : m[i]) j /= lazy[i];
        }
        return det;
    }
};
