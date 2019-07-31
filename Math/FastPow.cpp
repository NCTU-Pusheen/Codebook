#include<bits/stdc++.h>
using namespace std;
template <class T> T FastPow(T a, int p)
{
    T ans = 1;
    while(p)
    {
        if(p&1) ans *= a;
        a *= a;
        p >>= 1;
    }
    return ans;
}
int main()
{
    int a,b;
    cin >> a >> b;
    cout << FastPow(a,b);
    return 0;
}
