#include<iostream>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
#define w first
#define x second.first
#define y second.second
#define maxm 100000
#define maxn 10000
struct UFT
{
    int sz;
    int p[maxn];
    UFT(int _sz) {
        sz = _sz;
        for(int i=1; i<=sz; i++)
            p[i] = i;
    }
    inline int par(int a) {
        return p[a] = ( a==p[a] ? a : par(p[a]));
    }
    inline bool same(int a, int b) {
        return par(a) == par(b);
    }
    inline void uni(int a, int b) {
        p[p[a]] = p[b];
    }
};
int main()
{
    piii e[maxm];
    int n,m; cin >> n >> m;
    for(int i=0; i<m; i++)
        cin >> e[i].x >> e[i].y >> e[i].w;
    UFT uft(n); sort(e,e+m);
    int cnt = 0, cost = 0;
    for(int i=0; i<m && cnt<n-1; i++)
    {
        if( uft.same(e[i].x,e[i].y) ) continue;
        uft.uni(e[i].x,e[i].y);
        cnt++; cost += e[i].w;
    }
    if(cnt<n-1) cout << "Not connected!\n";
    else cout << "Cost = " << cost << endl;
    return 0;
}
