/* 三種 0/1-based。 只支援無向樹 */
/* Time: O(N+Q) Space: O(N^2) online */
class SsadpTarjan {
   private:
    int n;
    vector<int> par, dep; vector<vector<int>> ca;
    void dfs(int u, vector<vector<int>>& edge, int d) {
        dep[u] = d;
        for (int a = 0; a < n; a++)
            if (dep[a] != -1)
                ca[a][u] = ca[u][a] = parent(a);
        for (int a : edge[u]) {
            if (dep[a] != -1) continue;
            dfs(a, edge, d + 1);
            par[a] = u;
        }
    }
    int parent(int x) {
        if (par[x] == x) return x;
        return par[x] = parent(par[x]);
    }
   public:
    SsadpTarjan(vector<vector<int>>& edge, int root)
        : n(edge.size()) {
        dep.assign(n, -1); par.resize(n);
        ca.assign(n, vector<int>(n));
        for (int i = 0; i < n; i++) par[i] = i;
        dfs(root, edge, 0);
    }
    int lca(int a, int b) { return ca[a][b]; }
    int dist(int a, int b) {
        return dep[a] + dep[b] - 2 * dep[ca[a][b]];
    }
};
/* Time: O(N+Q)  Space: O(N+Q) only offline */
#define x first
#define y second
class OfflineTarjan {
   private:
    vector<int> par, anc, dep, ans, rank;
    vector<vector<pii>> qry;
    vector<vector<int>>& edge; // 安全考量可把 & 去掉
    int root, n;
    void merge(int a, int b) {
        a = parent(a), b = parent(b);
        if (rank[a] < rank[b]) swap(a, b);
        else if (rank[a] == rank[b]) rank[a]++;
        par[b] = a;
    }
    void dfs(int u, int d) {
        anc[parent(u)] = u, dep[u] = d;
        for (int a : edge[u]) {
            if (dep[a] != -1) continue;
            dfs(a, d + 1);
            merge(a, u);
            anc[parent(u)] = u;
        }
        for (auto q : qry[u])
            if (dep[q.first] != -1)
                ans[q.second] = anc[parent(q.first)];
    }
    int parent(int x) {
        if (par[x] == x) return x;
        return par[x] = parent(par[x]);
    }
    void solve(vector<pii>& query) {
        dep.assign(n, -1), rank.assign(n, 0);
        par.resize(n), anc.resize(n), qry.resize(n);
        for (int i = 0; i < n; i++) anc[i] = par[i] = i;
        ans.resize(query.size());
        for (int i = 0; i < query.size(); i++) {
            auto& q = query[i];
            qry[q.first].emplace_back(q.second, i);
            qry[q.second].emplace_back(q.first, i);
        }
        dfs(root, 0);
    }
   public:
    // edge 是傳 reference ，完成所有查詢不可改。
    OfflineTarjan(vector<vector<int>>& edge, int root)
        : edge(edge), root(root), n(edge.size()) {}
    // 離線查詢， query 陣列包含所有詢問 {src, dst} 。呼叫一次無
    // 論 query 量多少，複雜度都是 O(N) 。所以應盡量只呼叫一次。
    vector<int> lca(vector<pii>& query) {
        solve(query); return ans;
    }
    vector<int> dist(vector<pii>& query) {
        solve(query);
        for (int i = 0; i < query.size(); i++) {
            auto & q = query[i];
            ans[i] = dep[q.first] + dep[q.second]
                     - 2 * dep[ans[i]];
        } return ans;
    }
};
/* Udchen Time: O(QlgN) Space: O(NlgN) 。支援非離線。*/
class SparseTableTarjan {
   private:
    int maxlg;
    vector<vector<int>> anc;
    vector<int> dep;
    void dfs(int u, vector<vector<int>>& edge, int d) {
        dep[u] = d;
        for (int i = 1; i < maxlg; i++)
            if (anc[u][i - 1] == -1) break;
            else anc[u][i] = anc[anc[u][i - 1]][i - 1];
        for (int a : edge[u]) {
            if (dep[a] != -1) continue;
            anc[a][0] = u;
            dfs(a, edge, d + 1);
        }
    }
   public:
    SparseTableTarjan(vector<vector<int>>& edge, int root) {
        int n = edge.size();
        maxlg = ceil(log2(n));
        anc.assign(n, vector<int>(maxlg, -1));
        dep.assign(n, -1);
        dfs(root, edge, 0);
    }
    int lca(int a, int b) {
        if (dep[a] > dep[b]) swap(a, b);
        for (int k = 0; dep[b] - dep[a]; k++)
            if (((dep[b] - dep[a]) >> k) & 1) b = anc[b][k];
        if (a == b) return a;
        for (int k = maxlg - 1; k >= 0; k--)
            if (anc[a][k] != anc[b][k])
                a = anc[a][k], b = anc[b][k];
        return anc[a][0];
    }
    int dist(int a, int b) {
        return dep[a] + dep[b] - 2 * dep[lca(a, b)];
    }
};
