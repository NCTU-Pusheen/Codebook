//ZJ b417: 區間眾數
#define maxn 100005
#define maxq 1000005
struct Qry { int l, r, lid, id; };
bool cmp(const Qry &a, const Qry &b) {
    if(a.lid==b.lid)return a.r<b.r;
    return a.lid < b.lid;
}
Qry qry[maxq];
int ans[maxq][2];
int main() {
    int a[maxn];
    int t[maxn] = {};
    int cnt[maxn] = {};
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
    int k = sqrt(n);
    for(int i=0; i<q; i++) {
        scanf("%d%d",&qry[i].l,&qry[i].r);
        qry[i].id = i;
        qry[i].lid = qry[i].l / k;
    }
    sort(qry,qry+q,cmp);
    int l = qry[0].l+1, r = qry[0].l;
    int max_t = 0;
    for(int i=0; i<q; i++) {
        while(r<qry[i].r) {
            r++;
            cnt[t[a[r]]]--;
            t[a[r]]++;
            cnt[t[a[r]]]++;
            max_t = max(max_t,t[a[r]]);
        }
        while(qry[i].l<l) {
            l--;
            cnt[t[a[l]]]--;
            t[a[l]]++;
            cnt[t[a[l]]]++;
            max_t = max(max_t,t[a[l]]);
        }
        while(qry[i].l>l) {
            cnt[t[a[l]]]--;
            t[a[l]]--;
            cnt[t[a[l]]]++;
            l++;
            if(!cnt[max_t])max_t--;
        }
        while(r>qry[i].r) {
            cnt[t[a[r]]]--;
            t[a[r]]--;
            cnt[t[a[r]]]++;
            r--;
            if(!cnt[max_t])max_t--;
        }
        ans[qry[i].id][0] = max_t;
        ans[qry[i].id][1] = cnt[max_t];
    }
    for(int i=0; i<q; i++) printf("%d %d\n",ans[i][0],ans[i][1]);
    return 0;
}
