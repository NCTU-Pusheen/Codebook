// qsort suffix array, 0-based only, O(T * log^2 T) 略慢但是好寫
const int N = ? ;  // 字串最大長度
namespace SA {
int sa[N], t0[N], t1[N];

struct CMP {
    int *r, n, X;
    bool operator()(int i, int j) {
        if (r[i] != r[j]) return r[i] < r[j];
        int a = (i + n < X) ? r[i + n] : -1;
        int b = (j + n < X) ? r[j + n] : -1;
        return a < b;
    }
};

// str = 字串，可為 vector 或 string 或 char[] 等
// n = 字串長(含$)
// 結果存在 SA::sa
template <typename T>
void build(const T &str) {
    int n = str.size();
    int *a = t0, *aa = t1;
    for (int i = 0; i < n; i++) sa[i] = i, a[i] = str[i];
    for (int m = 2; m <= n; m *= 2) {
        CMP cmp = {a, m / 2, n};
        sort(sa, sa + n, cmp);
        int r = 0;
        aa[sa[0]] = r;
        for (int i = 1; i < n; i++) {
            if (cmp(sa[i - 1], sa[i])) r++;
            aa[sa[i]] = r;
        }
        swap(a, aa);
        if (r == n - 1) break;
    }
}
}  // namespace SA


// 卦長的 IS suffix array ，0-based only
// N = 字串最大長度 , A = 最大字元 ascii
// 複雜度 O(N+A)
const int N = ?, A = ?;
namespace SA {

#define pushS(x) sa[--b[s[x]]] = x
#define pushL(x) sa[b[s[x]]++] = x
#define induce_sort(v)                                    \
    {                                                     \
        fill_n(sa, n, 0);                                 \
        copy_n(bb, A, b);                                 \
        for (i = n1 - 1; ~i; --i) pushS(v[i]);            \
        copy_n(bb, A - 1, b + 1);                         \
        for (i = 0; i < n; ++i)                           \
            if (sa[i] && !t[sa[i] - 1]) pushL(sa[i] - 1); \
        copy_n(bb, A, b);                                 \
        for (i = n - 1; ~i; --i)                          \
            if (sa[i] && t[sa[i] - 1]) pushS(sa[i] - 1);  \
    }

template <typename T>
void sais(const T s, int n, int *sa, int *bb, int *p, bool *t, int A) {
    int *r = p + n, *s1 = p + n / 2, *b = bb + A;
    int n1 = 0, i, j, x = t[n - 1] = 1, y = r[0] = -1, cnt = -1;
    for (i = n - 2; ~i; --i) t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
    for (i = 1; i < n; ++i) r[i] = t[i] && !t[i - 1] ? (p[n1] = i, n1++) : -1;
    fill_n(bb, A, 0);
    for (i = 0; i < n; ++i) ++bb[s[i]];
    for (i = 1; i < A; ++i) bb[i] += bb[i - 1];
    induce_sort(p);
    for (i = 0; i < n; ++i)
        if (~(x = r[sa[i]]))
            j = y < 0 || memcmp(s + p[x], s + p[y], (p[x + 1] - p[x]) * sizeof(s[0])), s1[y = x] = cnt += j;
    if (cnt + 1 < n1)
        sais(s1, n1, sa, b, r, t + n, cnt + 1);
    else
        for (i = 0; i < n1; ++i) sa[s1[i]] = i;
    for (i = 0; i < n1; ++i) s1[i] = p[sa[i]];
    induce_sort(s1);
}

int sa[N];
int b[N + A], p[N * 2];
bool t[N * 2];

// 計算 suffix array ，字串須為 char[] 或 int[]， 不可為 string 或 vector
// s = 字串
// n = 字串長度(含$)
// 結果存在 SA::sa
template <typename T>
void build(const T s, int n) { sais(s, n, sa, b, p, t, A); }

}  // namespace SA

