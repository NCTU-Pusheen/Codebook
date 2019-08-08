//資芽2018
#include<iostream>
#include<string>
using namespace std;
void z_build(string &s, int *z)
{
    int bst = z[0] = 0;
    for(int i=1; s[i]; i++)
    {
        if( z[bst]+bst<i ) z[i] = 0;
        else z[i] = min( z[bst]+bst-i , z[i-bst] );
        while( s[z[i]] == s[i+z[i]] ) z[i]++;
        if( z[i]+i > z[bst]+bst ) bst = i;
    }
}
//s在t中出現幾次
int z_match(string &s, string &t)
{
    int ans = 0;
    int lens = s.length(), lent = t.length();
    int* z = new int[lens+lent+5];
    string st = s+"$"+t;
    z_build(st,z);
    for(int i=lens+1; i<=lens+lent; i++)
        if(z[i]==lens) ans++;
    return ans;
}
int main()
{
    string s,t;
    cin >> s >> t;
    cout << z_match(s,t) << endl;
    return 0;
}
