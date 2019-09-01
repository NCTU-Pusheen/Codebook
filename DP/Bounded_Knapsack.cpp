namespace {
    static const int MAXW = 1000005;
    static const int MAXN = 1005;
    struct BB {
        int w, v, c;
        BB(int w = 0, int v = 0, int c = 0): w(w), v(v), c(c) {}
        bool operator<(const BB &x) const {
            return w * c  < x.w * x.c;
        }
    };
    static int run(BB A[], int dp[], int W, int N) {
        static int MQ[MAXW][2];
        for (int i = 0, sum = 0; i < N; i++) {
            int w = A[i].w, v = A[i].v, c = A[i].c;
            sum = min(sum + w*c, W);
            for (int j = 0; j < w; j++) {
                int l = 0, r = 0;
                MQ[l][0] = 0, MQ[l][1] = dp[j];
                for (int k = 1, tw = w+j, tv = v; tw <= sum && k <= c; k++, tw += w, tv += v) {
                    int dpv = dp[tw] - tv;
                    while (l <= r && MQ[r][1] <= dpv) r--;
                    r++;
                    MQ[r][0] = k, MQ[r][1] = dpv;
                    dp[tw] = max(dp[tw], MQ[l][1] + tv);
                }
                for (int k = c+1, tw = (c+1)*w+j, tv = (c+1)*v; tw <= sum; k++, tw += w, tv += v) {
                    if (k - MQ[l][0] > c) l++;
                    int dpv = dp[tw] - tv;
                    while (l <= r && MQ[r][1] <= dpv) r--;
                    r++;
                    MQ[r][0] = k, MQ[r][1] = dpv;
                    dp[tw] = max(dp[tw], MQ[l][1] + tv);
                }
            }
        }
    }
    static int knapsack(int C[][3], int N, int W) { // O(WN)
        vector<BB> A;
        for (int i = 0; i < N; i++) {
            int w = C[i][0], v = C[i][1], c = C[i][2];
            A.push_back(BB(w, v, c));
        }
        assert(N < MAXN);
        static int dp1[MAXW+1], dp2[MAXW+1];
        BB Ar[2][MAXN];
        int ArN[2] = {};
        memset(dp1, 0, sizeof(dp1[0])*(W+1));
        memset(dp2, 0, sizeof(dp2[0])*(W+1));
        sort(A.begin(), A.end());
        int sum[2] = {};
        for (int i = 0; i < N; i++) {
            int ch = sum[1] < sum[0];
            Ar[ch][ArN[ch]] = A[i];
            ArN[ch]++;
            sum[ch] = min(sum[ch] + A[i].w*A[i].c, W);
        }
        run(Ar[0], dp1, W, ArN[0]);
        run(Ar[1], dp2, W, ArN[1]);
        int ret = 0;
        for (int i = 0, j = W, mx = 0; i <= W; i++, j--) {
            mx = max(mx, dp2[i]);
            ret = max(ret, dp1[j] + mx);
        }
        return ret;
    }
}
int main() {
    int W, N;
    assert(scanf("%d %d", &W, &N) == 2);
    int C[MAXN][3];
    for (int i = 0; i < N; i++)
        assert(scanf("%d %d %d", &C[i][1], &C[i][0], &C[i][2]) == 3);
    printf("%d\n", knapsack(C, N, W));
    return 0;
}
