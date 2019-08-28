//LCA //Tarjan's algorithm
#define maxv 100
int LCA[maxv][maxv]; //lowest common ancestor
vector<int> v[maxv]; //adjacency lists
int p[maxv]; //parent
bool visit[maxv]; //false
int n; //the number of vertex
void init() { for(int i=0; i<n; i++) p[i]=i; }
int parent(int x) { return (p[x]==x) ? (p[x]=parent(x)) : x); }
int dfs(int u) {
    visit[u] = true;
    for(int i=0; i<n; i++)
        if(visit[i]) LCA[i][u] = LCA[u][i] = parent(i);
    for(int i=v[u].size()-1; i>=0; i--) {
        int uu = v[u][i];
        if(!visit[uu]) { dfs(uu); p[uu] = u; }
    }
}
void Tarjan() { init(); dfs(0); }
