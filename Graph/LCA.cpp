// Tarjan
// Time Complexity: O(N+Q)
// Space Complexity: O(N^2)

class Tarjan {
   private:
    const int N;
    vector<int> par;
    vector<int> dep;
    vector<vector<int>> ca;

    int dfs(int u, const vector<vector<int>>& edge, int d) {
        dep[u] = d;

        for (int a = 0; a < N; a++)
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
    Tarjan(const vector<vector<int>>& edge, int root) : N(edge.size()) {
        dep.assign(N, -1);
        par.resize(N);
        ca.assign(N, vector<int>(N));

        for (int i = 0; i < N; i++) par[i] = i;
        dfs(root, edge, 0);
    }

    int lca(int a, int b) { return ca[a][b]; }

    int dist(int a, int b) {
        int acc = ca[a][b];
        return dep[a] - dep[acc] + dep[b] - dep[acc];
    }
};

// HakkaTarjan
// Time Complexity: O(N+Q)
// Space Complexity: O(N+Q)
// OFFLINE REQUIRED

class HakkaTarjan {
   private:
    vector<int> par;
    vector<int> anc;
    vector<int> dep;
    vector<vector<pii>> qry;
    vector<int> ans;
    vector<int> rank;

    const int N;
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
        dep.assign(N, -1);
        rank.assign(N, 0);
        par.resize(N);
        anc.resize(N);
        for (int i = 0; i < N; i++) anc[i] = par[i] = i;

        ans.resize(query.size());
        qry.resize(N);
        for (int i = 0; i < query.size(); i++) {
            auto& q = query[i];
            qry[q.first].emplace_back(q.second, i);
            qry[q.second].emplace_back(q.first, i);
        }

        dfs(root, 0);
    }

   public:
    // O(1)
    HakkaTarjan(const vector<vector<int>>& edge, int root) : N(edge.size()), edge(edge), root(root) {}

    // O(N+Q)
    vector<int> lca(const vector<pii>& query) {
        solve(query);
        return ans;
    }

    vector<int> dist(const vector<pii>& query) {
        solve(query);
        for (int i = 0; i < query.size(); i++) {
            auto& q = query[i];
            ans[i] = dep[q.first] + dep[q.second] - 2 * dep[ans[i]];
        }
        return ans;
    }
};