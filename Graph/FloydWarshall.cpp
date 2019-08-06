#include<iostream>
#include<vector>
using namespace std;
#define maxn 505
#define INF 10000000
typedef pair<int,int> pii;
vector<pii> G[maxn];
int dist[maxn][maxn];
void FloydWarshalll(int n)
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            dist[i][j] = i==j?0:INF;
    for(int i=1; i<=n; i++)
        for(pii j:G[i])
            dist[i][j.first] = j.second;
    for(int k=1; k<=n; k++) //DP //O(n^3)
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
}
int main()
{
    int n,m,q;
    cin >> n >> m >> q;
    for(int i=0; i<m; i++)
    {
        int u,v,d;
        cin >> u >> v >> d;
        G[u].push_back(pii(v,d));
    }
    FloydWarshalll(n);
    while(q--)
    {
        int u,v;
        cin >> u >> v;
        if(dist[u][v]==INF)printf("(%d,%d) not connected\n",u,v);
        printf("Dist(%d,%d)=%d\n",u,v,dist[u][v]);
    }
    return 0;
}
