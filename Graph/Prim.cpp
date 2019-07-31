#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define maxn 1000
#define INF 2100000000
bool Prim(int n,vector<pii> G[],int &cost)
{
    cost = 0;
    int d[maxn];
    bool visit[maxn] = {};
    for(int i=1; i<=n; i++)
        d[i] = INF;
    d[1] = 0;
    priority_queue<pii> pq;
    pq.push({0,1});
    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if(visit[u])continue;
        visit[u] = true;
        cost += d[u];
        for(pii e:G[u])
        {
            int v = e.first;
            int w = e.second;
            if( d[v] > w )
            {
                d[v] = w;
                pq.push({d[v],v});
            }
        }
    }
    for(int i=1; i<=n; i++)
        if(!visit[i])return false;
    return true;
}
int main()
{
    vector<pii> G[maxn];
    int d[maxn];
    int n,m;
    cin >> n >> m;
    for(int i=1; i<=m; i++)
    {
        int a,b,w;
        cin >> a >> b >> w;
        G[a].push_back({b,w});
    }
    int cost = 0;
    if(Prim(n,G,cost))printf("cost = %d\n",cost);
    else printf("Can't build a tree.");
    return 0;
}
