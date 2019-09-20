// SsadpTarjan (fastest but space comsuming)
// Time Complexity: O(N+Q)
// Space Complexity: O(N^2)
class SsadpTarjan {
   private:
    const int n;
    vector<int> par;
    vector<int> dep;
    vector<vector<int>> ca;

    int dfs(int u, const vector<vector<int>>& edge, int d) {
        dep[u] = d;

        for (int a = 0; a < n; a++)
            if (dep[a] != -1) ca[a][u] = ca[u][a] = parent(a);

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
    SsadpTarjan(const vector<vector<int>>& edge, int root) : n(edge.size()) {
        dep.assign(n, -1);
        par.resize(n);
        ca.assign(n, vector<int>(n));

        for (int i = 0; i < n; i++) par[i] = i;
        dfs(root, edge, 0);
    }

    int lca(int a, int b) { return ca[a][b]; }

    int dist(int a, int b) { return dep[a] + dep[b] - 2 * dep[ca[a][b]]; }
};

// OfflineTarjan (fastest and space saving but offline required)
// Time Complexity: O(N+Q)
// Space Complexity: O(N+Q)
// OFFLINE REQUIRED
class OfflineTarjan {
   private:
    vector<int> par;
    vector<int> anc;
    vector<int> dep;
    vector<vector<pii>> qry;
    vector<int> ans;
    vector<int> rank;

    const int n;
    const vector<vector<int>>& edge;
    const int root;

    void merge(int a, int b) {
        a = parent(a), b = parent(b);
        if (rank[a] < rank[b]) swap(a, b);
        par[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
    }

    void dfs(int u, int d) {
        anc[parent(u)] = u;
        dep[u] = d;

        for (int a : edge[u]) {
            if (dep[a] != -1) continue;
            dfs(a, d + 1);
            merge(a, u);
            anc[parent(u)] = u;
        }

        for (auto q : qry[u]) {
            if (dep[q.first] != -1) ans[q.second] = anc[parent(q.first)];
        }
    }

    int parent(int x) {
        if (par[x] == x) return x;
        return par[x] = parent(par[x]);
    }

    void solve(const vector<pii>& query) {
        dep.assign(n, -1);
        rank.assign(n, 0);
        par.resize(n);
        anc.resize(n);
        for (int i = 0; i < n; i++) anc[i] = par[i] = i;

        ans.resize(query.size());
        qry.resize(n);
        for (int i = 0; i < query.size(); i++) {
            auto& q = query[i];
            qry[q.first].emplace_back(q.second, i);
            qry[q.second].emplace_back(q.first, i);
        }

        dfs(root, 0);
    }

   public:
    OfflineTarjan(const vector<vector<int>>& edge, int root) : n(edge.size()), edge(edge), root(root) {}

    // O(N+Q)
    vector<int> lca(const vector<pii>& query) {
        solve(query);
        return ans;
    }

    // O(N+Q)
    vector<int> dist(const vector<pii>& query) {
        solve(query);
        for (int i = 0; i < query.size(); i++) {
            auto& q = query[i];
            ans[i] = dep[q.first] + dep[q.second] - 2 * dep[ans[i]];
        }
        return ans;
    }
};

// SparseTableTarjan (eclectic and somehow slower)
// Time Complexity: O(N+QlogN)
// Space complexity: O(NlogN)
class SparseTableTarjan {
   private:
    const int maxlg;
    const int n;
    vector<vector<int>> anc;
    vector<int> dep;

    void dfs(int u, const vector<vector<int>>& edge, int d) {
        dep[u] = d;
        for (int i = 1; i < maxlg; i++)
            if (anc[u][i - 1] < 0)
                anc[u][i] = -1;
            else
                anc[u][i] = anc[anc[u][i - 1]][i - 1];
        for (int a : edge[u]) {
            if (dep[a] != -1) continue;
            anc[a][0] = u;
            dfs(a, edge, d + 1);
        }
    }

   public:
    SparseTableTarjan(const vector<vector<int>>& edge, int root) : n(edge.size()), maxlg(__lg(n)) {
        anc.assign(n, vector<int>(maxlg));
        dep.assign(n, -1);
        dfs(root, edge, 0);
    }

    // O(logN)
    int lca(int a, int b) {
        if (dep[a] > dep[b]) swap(a, b);
        for (int k = 0; k < maxlg; k++)
            if ((dep[b] - dep[a]) >> k & 1) b = anc[b][k];

        if (a == b) return a;
        for (int k = maxlg - 1; k >= 0; k--)
            if (anc[a][k] != anc[b][k]) a = anc[a][k], b = anc[b][k];
        return anc[a][0];
    }

    // O(logN)
    int dist(int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }
};