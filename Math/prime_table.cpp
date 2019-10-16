#include<stdio.h>
#define MAX 40000
using namespace std;
bool isprime[MAX]; //全域變數初始值為false
int prime[5000];
int p; //紀錄質數數量
void build_table() {
    isprime[0] = true, isprime[1] = true, isprime[2] = false;
    prime[1] = 2;
    p = 2;
    for(int i=4; i<MAX; i+=2) isprime[i] = true; //偶數先刪
    for(int i=3; i<MAX; i+=2) //處理奇數
    {
        if(!isprime[i]) {
            prime[p++]=i;
            for(int j=i*i; j<MAX; j+=2*i) isprime[j]=true;
            //小於i*i的合數必有小於i的質因數
        }
    }//printf("%d\n",p); //小於40000的質數有4204個
}
int main() {
    build_table();
    int n;
    while( scanf("%d",&n)==1 && n>0 && n<p ) {
        //find the n'th prime number
        printf("prime[%d]=%d.\n",n,prime[n]);
    }
    return 0;
}