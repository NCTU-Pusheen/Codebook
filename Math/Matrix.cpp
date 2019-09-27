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

struct Matrix {
    const int r, c;
    vector<vector<ll>> m;
    Matrix(int r, int c) : r(r), c(c), m(r, vector<ll>(c)) {}

    // Element access operator
    vector<ll> &operator[](int i) { return m[i]; }
    // Performs increment
    Matrix operator+(const Matrix &a) const {
        Matrix rev(r, c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j) rev[i][j] = m[i][j] + a.m[i][j];
        return rev;
    }
    // Performs substraction
    Matrix operator-(const Matrix &a) const {
        Matrix rev(r, c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j) rev[i][j] = m[i][j] - a.m[i][j];
        return rev;
    }
    // Performs multiplication
    Matrix operator*(const Matrix &a) const {
        Matrix rev(r, a.c);
        Matrix tmp(a.c, a.r);
        for (int i = 0; i < a.r; ++i)
            for (int j = 0; j < a.c; ++j) tmp[j][i] = a.m[i][j];
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < a.c; ++j)
                for (int k = 0; k < c; ++k) rev.m[i][j] += m[i][k] * tmp[j][k];
        return rev;
    }
    // Queries inverse of this matrix. If this matrix is not inversible, a 0*0 matrix is returned.
    Matrix inverse() const {
        Matrix t(r, r + c);
        for (int y = 0; y < r; y++) {
            t.m[y][c + y] = 1;
            for (int x = 0; x < c; ++x) t.m[y][x] = m[y][x];
        }
        if (!t.gas()) return Matrix(0, 0);

        Matrix ret(c, r);
        for (int y = 0; y < r; y++)
            for (int x = 0; x < c; ++x) ret[y][x] = t.m[y][c + x] / t.m[y][y];
        return ret;
    }

    // A helper function for inverse.
    ll gas() {
        vector<ll> lazy(r, 1);
        bool sign = false;
        for (int i = 0; i < r; ++i) {
            if (m[i][i] == 0) {
                int j = i + 1;
                while (j < r && !m[j][i]) j++;
                if (j == r) continue;
                m[i].swap(m[j]);
                sign = !sign;
            }
            for (int j = 0; j < r; ++j) {
                if (i == j) continue;
                lazy[j] = lazy[j] * m[i][i];
                ll mx = m[j][i];
                for (int k = 0; k < c; ++k) m[j][k] = m[j][k] * m[i][i] - m[i][k] * mx;
            }
        }
        ll det = sign ? -1 : 1;
        for (int i = 0; i < r; ++i) {
            det = det * m[i][i];
            det = det / lazy[i];
            for (auto &j : m[i]) j /= lazy[i];
        }
        return det;
    }
};
