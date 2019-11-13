vector<pii> G[maxn];
int dis[maxn];
bool BellmanFord(int n,int s) {
    for(int i=1; i<=n; i++) dis[i] = INF;
    dis[s] = 0;
    bool relax;
    for(int r=1; r<=n; r++) { //O(VE)
        relax = false;
        for(int i=1; i<=n; i++)
            for(pii e:G[i])
                if( dis[i] + e.second < dis[e.first] )
                    dis[e.first] = dis[i] + e.second, relax = true;
    }
    return relax; //有負環
}
