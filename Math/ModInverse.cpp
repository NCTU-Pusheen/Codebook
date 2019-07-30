//用輾轉相除法求模逆元
#include<bits/stdc++.h>
using namespace std;
int exgcd(int a,int b,int &x,int &y)
{
    if(b)
    {
        int tmp = exgcd(b,a%b,y,x);
        y -= a/b*x;
        return tmp;
    }
    x = 1, y = 0;
    return a;
}
int main()
{
    int a,b,x,y;
    while(cin >> a >> b)
    {
        exgcd(a,b,x,y);
        cout << (x%b+b)%b << endl;
    }
    return 0;
}
