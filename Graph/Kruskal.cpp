#include<iostream>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
#define w first
#define x second.first
#define y second.second
#define maxm 1000000
#define maxn 100000
struct UFT //Union-Find Tree
{
    int sz[maxn], n;
    int p[maxn];
    UFT(int _n) {
        n = _n;
        for(int i=0; i<=n; i++)
            p[i] = i, sz[i] = 1;
    }
    inline int par(int a) { //parent
        return p[a] = ( a==p[a] ? a : par(p[a]));
    }
    inline bool same(int a, int b) { //check if a and b are in the same set
        return par(a) == par(b);
    }
    inline void uni(int a, int b) { //union the sets of a and b
        a = par(a), b = par(b);
        if (a == b) return;
        if (sz[a] >= sz[b]) p[b] = a;
    	else p[a] = b;
    }
};
piii e[maxm];
int main()
{
    int n,m; cin >> n >> m;
    for(int i=0; i<m; i++)
        cin >> e[i].x >> e[i].y >> e[i].w;
    UFT uft(n); sort(e,e+m); //sort the edges
    int cnt = 0, cost = 0;
    for(int i=0; i<m && cnt<n-1; i++)
    {
        if( uft.same(e[i].x,e[i].y) ) continue;
        uft.uni(e[i].x,e[i].y);
        cnt++; cost += e[i].w;
    }
    if(cnt<n-1) cout << "-1\n";
    else cout << cost << '\n';
    return 0;
}
