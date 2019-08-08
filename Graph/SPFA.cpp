#include<vector>
#include<queue>
#include<iostream>
using namespace std;
#define maxn 2000
#define INF 100000000
typedef pair<int,int> pii;
vector<pii> G[maxn];
int dis[maxn];
void SPFA(int n,int s) //O(kE) k~2.
{
    for(int i=1; i<=n; i++)
        dis[i] = INF;
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    bool inque[maxn] = {};
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        inque[u] = false;
        for(pii e:G[u])
        {
            int v = e.first , w = e.second;
            if( dis[u] + w < dis[v])
            {
                if(!inque[v]) q.push(v), inque[v] = true;
                dis[v] = dis[u] + w;
            }
        }
    }
}
int main()
{
    int n,m; cin >> n >> m;
    for(int i=0; i<m; i++)
    {
        int a,b,w;
        cin >> a >> b >> w;
        G[a].push_back(pii(b,w));
    }
    int s,t;
    cin >> s >> t;
    SPFA(n,s);
    if(dis[t]==INF) cout << "dis = INF\n";
    else cout << "dis = " << dis[t] << endl;
    return 0;
}
