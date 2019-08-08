#include<vector>
#include<iostream>
using namespace std;
#define maxn 2000
#define INF 100000000
typedef pair<int,int> pii;
vector<pii> G[maxn];
int dis[maxn];
bool BellmanFord(int n,int s)
{
    for(int i=1; i<=n; i++)
        dis[i] = INF;
    dis[s] = 0;
    bool relax;
    for(int r=1; r<=n; r++) //O(VE)
    {
        relax = false;
        for(int i=1; i<=n; i++)
            for(pii e:G[i])
                if( dis[i] + e.second < dis[e.first] )
                    dis[e.first] = dis[i] + e.second, relax = true;
    }
    return relax; //有負環
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
    if(BellmanFord(n,s)) cout << "There is a minus-cycle.\n";
    else cout << "dis = " << dis[t] << endl;
    return 0;
}
