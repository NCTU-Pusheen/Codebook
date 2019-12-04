using namespace std;
const int maxn = 1e6 + 10;
struct query { int id, bk, l, r; };
int arr[maxn], cnt[maxn], d[maxn], n, m, bk, mx;
pair<int,int> ans[maxn];
vector<query> q;
bool cmp(query x,query y) {
    return (x.bk < y.bk || (x.bk == y.bk) && x.r < y.r);
}
void add(int pos) {
    d[cnt[arr[pos]]]--;
    cnt[arr[pos]]++;
    d[cnt[arr[pos]]]++;
    if(d[mx + 1] > 0) mx++;
}
void del(int pos) { 
    d[cnt[arr[pos]]]--; 
    cnt[arr[pos]]--;
    d[cnt[arr[pos]]]++;
    if(d[mx] == 0) mx--;
}
void mo(int n, int m) {
    sort(q.begin(), q.end(), cmp);
    for(int i = 0, cl = 1, cr = 0; i < m; i++) {
        while(cr < q[i].r) add(++cr);
        while(cl > q[i].l) add(--cl);
        while(cr > q[i].r) del(cr--);
        while(cl < q[i].l) del(cl++);
        ans[q[i].id] = make_pair(mx, d[mx]);
    }
}
int main(){
    cin >> n >> m;
    bk = (int)sqrt(n + 0.5);
    for(int i = 1; i <= n; i++) cin >> arr[i];
    q.resize(m);
    for(int i = 0; i < m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i,q[i].bk = (q[i].l - 1) / bk;
    }
    mo(n, m);
    for(int i = 0; i < m; i++)
        cout << ans[i].first << ' ' << ans[i].second << '\n';
    return 0;
}
