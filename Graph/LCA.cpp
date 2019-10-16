/**
 * Support fatest online query but consume more spaces. 0-
 * or 1-based are both safe and no needs to modify any
 * codes.
 *
 * Time Complexity: O(N+Q)
 * Space Complexity: O(N^2)
 */
class SsadpTarjan {
   private:
    int n;
    vector<int> par;
    vector<int> dep;
    vector<vector<int>> ca;

    int dfs(int u, vector<vector<int>>& edge, int d) {
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
    // Constructs a tarjan by adjacent edge information.
    // The vector in edge[i] gives indices of all adjacent
    // vertex of node of index i. Size of edge is unlimited,
    // but on 1-based cases, effective information should be
    // placed in range [1, n]; 0-based [0, n)
    SsadpTarjan(vector<vector<int>>& edge, int root)
        : n(edge.size()) {
        dep.assign(n, -1);
        par.resize(n);
        ca.assign(n, vector<int>(n));

        for (int i = 0; i < n; i++) par[i] = i;
        dfs(root, edge, 0);
    }

    // Queries least commom ancestor of node a and b.
    int lca(int a, int b) { return ca[a][b]; }

    // Queries minimal distance from node a to b.
    int dist(int a, int b) {
        return dep[a] + dep[b] - 2 * dep[ca[a][b]];
    }
};
class OfflineTarjan {
   private:
    vector<int> par;
    vector<int> anc;
    vector<int> dep;
    vector<vector<pii>> qry;
    vector<int> ans;
    vector<int> rank;

    // You can set this to non-reference type for safety
    // reasons
    vector<vector<int>>& edge;
    int root, n;

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
            if (dep[q.first] != -1)
                ans[q.second] = anc[parent(q.first)];
        }
    }

    int parent(int x) {
        if (par[x] == x) return x;
        return par[x] = parent(par[x]);
    }

    void solve(vector<pii>& query) {
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
    // Constructs a tarjan by adjacent edge information.
    // The vector in edge[i] gives indices of all adjacent
    // vertex of node of index i. Size of edge is unlimited,
    // but on 1-based cases, effective information should be
    // placed in range [1, n]; 0-based [0, n)
    OfflineTarjan(vector<vector<int>>& edge, int root)
        : edge(edge), root(root), n(edge.size()) {}

    // Given a data set of lca requests, queries least
    // commom ancestors of pairs of nodes. The result set
    // has same order to the data set.
    vector<int> lca(vector<pii>& query) {
        solve(query);
        return ans;
    }

    // Given a data set of minimal distance requests,
    // queries minimal distance within a pair of nodes in
    // each set. The result set has same order to the data
    // set.
    vector<int> dist(vector<pii>& query) {
        solve(query);
        for (int i = 0; i < query.size(); i++) {
            auto& q = query[i];
            ans[i] = dep[q.first] + dep[q.second] -
                     2 * dep[ans[i]];
        }
        return ans;
    }
};

/**
 * Support a little slower query and save spaces.
 *
 * Time Complexity: O(N+QlogN)
 * Space complexity: O(NlogN)
 */
class SparseTableTarjan {
   private:
    int maxlg;
    vector<vector<int>> anc;
    vector<int> dep;

    void dfs(int u, vector<vector<int>>& edge, int d) {
        dep[u] = d;

        for (int i = 1; i < maxlg; i++)
            if (anc[u][i - 1] == -1)
                break;
            else
                anc[u][i] = anc[anc[u][i - 1]][i - 1];

        for (int a : edge[u]) {
            if (dep[a] != -1) continue;
            anc[a][0] = u;
            dfs(a, edge, d + 1);
        }
    }

   public:
    // Constructs a tarjan by adjacent edge information.
    // The vector in edge[i] gives indices of all adjacent
    // vertex of node of index i. Size of edge is unlimited,
    // but on 1-based cases, effective information should be
    // placed in range [1, n]; 0-based [0, n)
    SparseTableTarjan(vector<vector<int>>& edge, int root) {
        int n = edge.size();
        maxlg = ceil(log2(n));
        anc.assign(n, vector<int>(maxlg, -1));
        dep.assign(n, -1);
        dfs(root, edge, 0);
    }

    // Queries least commom ancestor of node a and b.
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

    // Queries minimal distance from node a to b.
    int dist(int a, int b) {
        return dep[a] + dep[b] - 2 * dep[lca(a, b)];
    }
};