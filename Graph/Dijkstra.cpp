#include<bits/stdc++.h>
using namespace std;
#define INF 2100000000
#define maxn 1000
typedef pair<int,int> pii;
void Dijkstra(int n, vector<pii> G[], int d[], int s, int t = -1)
{
    for(int i=1; i<=n; i++)
        d[i] = INF;
    d[s] = 0;
    priority_queue<pii> pq;
    pq.push({0,s});
    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if(u==t)return;
        for(pii e:G[u])
        {
            int v = e.first;
            int w = e.second;
            if( d[v] > d[u]+w )
            {
                d[v] = d[u]+w;
                pq.push({d[v],v});
            }
        }
    }
}
int main()
{
    vector<pii> G[maxn];
    int d[maxn];
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=m;i++)
    {
        int a,b,w;
        cin >> a >> b >> w;
        G[a].push_back({b,w});
    }
    int s,t;
    cin >> s >> t;
    Dijkstra(n,G,d,s,t);
    printf("%d\n",d[t]);
    return 0;
}
