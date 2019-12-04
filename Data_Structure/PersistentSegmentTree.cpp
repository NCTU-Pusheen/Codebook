int a[maxn], b[maxn], root[maxn], cnt;
struct node {
    int sum, L_son, R_son;
} tree[maxn << 5];
int create(int _sum, int _L_son, int _R_son) {
    int idx = ++cnt;
    tree[idx].sum = _sum, tree[idx].L_son = _L_son, tree[idx].R_son = _R_son;
    return idx;
}
void Insert(int &root, int pre_rt, int pos, int L, int R) {
    root = create(tree[pre_rt].sum+1, tree[pre_rt].L_son, tree[pre_rt].R_son);
    if(L==R) return;
    int M = (L+R)>>1;
    if(pos<=M) Insert(tree[root].L_son, tree[pre_rt].L_son, pos, L, M);
    else Insert(tree[root].R_son, tree[pre_rt].R_son, pos, M+1, R);
}
int query(int L_id, int R_id, int L, int R, int K) {
    if(L==R) return L;
    int M = (L+R)>>1;
    int s = tree[tree[R_id].L_son].sum - tree[tree[L_id].L_son].sum;
    if(K<=s) return query(tree[L_id].L_son, tree[R_id].L_son, L, M, K);
    return query(tree[L_id].R_son, tree[R_id].R_son, M+1, R, K-s);
}
int main() {
    int n,m; cin >> n >> m
    for(int i=1; i<=n; i++) {
        cin >> a[i]; b[i] = a[i];
    } sort(b+1,b+1+n); //離散化
    int b_sz = unique(b+1, b+1+n) - (b+1);
    cnt = root[0] = 0;
    for(int i=1; i<=n; i++) {
        int pos = lower_bound(b+1, b+1+b_sz, a[i]) - b;
        Insert(root[i], root[i-1], pos, 1, b_sz);
    }
    while(m--) {
        int l, r, k; cin >> l >> r >> k;
        int pos = query(root[l-1],root[r],1,b_sz,k);
        cout << b[pos] << endl;
    } return 0;
}
