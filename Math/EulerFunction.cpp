//Euler's totient function
// phi(n):=不大於n且與n互質的正整數個數
// If p is prime, then phi(p^k) = p^k - p^(k-1)
// If gcd(m,n) = 1, then phi(mn) = phi(m)phi(n)
#include<stdio.h>
using namespace std;
#define maxn 1000000
int phi[maxn];
bool not_prime[maxn];
void Euler(int n)
{
    not_prime[0] = not_prime[1] = true;
    for(int i=0; i<=n; i++)
        phi[i] = i;
    for(int i=2; i<=n; i++)
    {
        if(not_prime[i])continue;
        phi[i]--;
        for(int j=i<<1; j<=n; j+=i)
        {
            not_prime[j] = true;
            phi[j] = phi[j]/i*(i-1);
        }
    }
}
int main()
{
    Euler(100);
    for(int i=1;i<=100;i++)
        printf("%d:%d\n",i,phi[i]);
    return 0;
}
