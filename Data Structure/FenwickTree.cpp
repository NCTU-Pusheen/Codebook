//區間修改 //區間查詢
//來源：https://www.itread01.com/content/1528781928.html
#include<iostream>
using namespace std;
#define maxn 100000
//a[0] = 0
//d[i] = a[i]-a[i-1]
//a[i] = d[i]+d[i-1]+...d[1]
//dd[i] = d[i]*i;
//開兩個陣列紀錄d和dd的前綴和
class BIT
{
private:
    int sz = 0;
    int d[maxn] = {0};
    int dd[maxn] = {0};
    inline int lowbit(int x)
    {
        return (-x)&x;
    }
    int prefix_sum(int x)
    {
        int ans1 = 0, ans2 = 0;
        for(int i=x; i>0; i-=lowbit(i) )
            ans1 += d[i], ans2 += dd[i];
        return (x+1)*ans1 - ans2;
    }
    void update(int x, int v)
    {
        for(int i=x; i<=sz; i+=lowbit(i) )
            d[i] += v, dd[i] += x*v;
    }
public:
    BIT(int n){sz = n;}
    inline void add(int l,int r,int v)
    {
        update(l,v), update(r+1,-v);
    }
    inline int query(int l,int r)
    {
        return prefix_sum(r) - prefix_sum(l-1);
    }
};
int main()
{
    int n;  cin >> n;
    BIT bit(n);
    string op;
    while(cin >> op)
    {
        int l,r,v;
        if(op == "add")
        {
            cin >> l >> r >> v;
            bit.add(l,r,v);
        }
        else
        {
            cin >> l >> r;
            cout << bit.query(l,r) << endl;
        }
    }
    return 0;
}
