#include<bits/stdc++.h>
using namespace std;
#define maxn 500005
#define lgn 20
int a[maxn];
int ST[lgn][maxn];
void buildST(int n)
{
    for(int i=1; i<=n; i++)
        ST[0][i] = a[i];
    for(int i=1; (1<<i)<=n; i++)
    {
        int k = n-(1<<i)+1;
        for(int j=1; j<=k; j++)
            ST[i][j] = max( ST[i-1][j] , ST[i-1][j+(1<<(i-1))] );
    }
}
inline int query(int l,int r)
{
    int k = __lg(r-l+1);
    return max( ST[k][l] , ST[k][r-(1<<k)+1] );
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
    buildST(n);
    while(q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",query(l,r));
    }
    return 0;
}
