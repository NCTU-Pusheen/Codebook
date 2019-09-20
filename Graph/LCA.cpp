// Time: O(N+Q)
// Space: O(N^2)

class Tarjan {
   private:
    const int N;
    vector<int> par;
    vector<int> dep;
    vector<vector<int>> lca;

    int dfs(int u, const vector<vector<int>>& edge, int d) {
        dep[u] = d;

        for (int a = 0; a < N; a++)
            if (dep[a] != -1) lca[a][u] = lca[u][a] = parent(a);

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
    // O(N)
    Tarjan(const vector<vector<int>>& edge, int root) : N(edge.size()) {
        dep.assign(N, -1);
        par.resize(N);
        lca.assign(N, vector<int>(N));

        for (int i = 0; i < N; i++) par[i] = i;
        dfs(root, edge, 0);
    }

    // O(1)
    int find_lca(int a, int b) { return lca[a][b]; }

    // O(1)
    int min_dist(int a, int b) {
        int acc = lca[a][b];
        return dep[a] - dep[acc] + dep[b] - dep[acc];
    }
};