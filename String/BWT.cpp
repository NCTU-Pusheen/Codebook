const int N = 8;            // 字串長度
int s[N+N+1] = "suffixes";  // 字串，後面預留一倍空間。
int sa[N];                  // 後綴陣列
int pivot;
int cmp(const void* i, const void* j) {
    return strncmp(s+*(int*)i, s+*(int*)j, N);
}
// 此處便宜行事，採用 O(N²logN) 的後綴陣列演算法。
void BWT() {
    strncpy(s + N, s, N);
    for (int i=0; i<N; ++i) sa[i] = i;
    qsort(sa, N, sizeof(int), cmp);
    // 當輸入字串的所有字元都相同，必須當作特例處理。
    // 或者改用stable sort。
    for (int i=0; i<N; ++i)
        cout << s[(sa[i] + N-1) % N];
    for (int i=0; i<N; ++i)
        if (sa[i] == 0) {
            pivot = i;
            break;
        }
}
// Inverse BWT
const int N = 8;            // 字串長度
char t[N+1] = "xuffessi";   // 字串
int pivot;
int next[N];
void IBWT() {
    vector<int> index[256];
    for (int i=0; i<N; ++i)
        index[t[i]].push_back(i);
    for (int i=0, n=0; i<256; ++i)
        for (int j=0; j<index[i].size(); ++j)
            next[n++] = index[i][j];
    int p = pivot;
    for (int i=0; i<N; ++i)
        cout << t[p = next[p]];
}
