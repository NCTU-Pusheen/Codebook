//抄日月卦長
//Knuth-Morris-Pratt algorithm
//問s有沒有在t出現
#include<iostream>
#include<string.h>
using namespace std;
#define LEN 10000
void KMP_fail(const char *s, int *F) //O(|s|)
{
    int p = F[0] = -1;
    for(int i=1; s[i]; i++)
    {
        while( p!=-1 && s[p+1]!=s[i] )
            p = F[p];
        if( s[p+1]==s[i] ) p++;
        F[i] = p;
    }
}
int KMP_match(const char *t, const char *s, int *F) //O(|t|)
{
    int p = -1, ans = 0;
    int len = strlen(s);
    for(int i=0; t[i]; i++)
    {
        while( p!=-1 && s[p+1]!=t[i] )
            p = F[p];
        if( s[p+1]==t[i] ) p++;
        if( p == len-1 )
            p = F[p], ans++;
    }
    return ans;
}
int main()
{
    char s[LEN],t[LEN];
    int F[LEN];
    cin >> t >> s;
    KMP_fail(s,F);
    cout << KMP_match(t,s,F) << endl;
    return 0;
}
