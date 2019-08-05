//單點修改 區間查詢
#include<bits/stdc++.h>
using namespace std;
class BIT
{
public:
    BIT(int n)
    {
        sz = n;
        bit = new int[sz+1];
        memset(bit,0,sizeof(int)*(sz+1));
    }
    ~BIT()
    {
        delete [] bit;
    }
private:
    int* bit;
    int sz;
    inline int lowbit(int x)
    {
        return x&(-x);
    }
    int prefix_sum(int x)
    {
        int sum = 0;
        for(int i=x; i>0; i-=lowbit(i))
            sum += bit[i];
        return sum;
    }
public:
    void init(int a[])//注意index
    {
        for(int i=1; i<=sz; i++)
        {
            bit[i] += a[i];
            int y = i+lowbit(i);
            if(y<=sz)
                bit[y] += bit[i];
        }
    }
    inline int query(int l,int r)
    {
        return prefix_sum(r) - prefix_sum(l-1);
    }
    void add(int x,int val)
    {
        for(int i=x; i<=sz; i+=lowbit(i))
            bit[i] += val;
    }
};
int main()
{
    BIT b(5);
    int a[6] = {0,1,2,3,4,5};
    b.init(a);
    string op;
    while(cin>>op)
    {
        if(op=="add")
        {
            int x,val;
            cin >> x >> val;
            b.add(x,val);
        }
        if(op=="sum")
        {
            int l,r;
            cin >> l >> r;
            cout << b.query(l,r) << endl;
        }
    }
    return 0;
}
