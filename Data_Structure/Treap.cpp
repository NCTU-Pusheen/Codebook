//POJ 3580 區間反轉＋加值 詢問min
#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define INF 2147483647
struct Treap
{
    Treap *L, *R;
    int min_val, size, val;
    bool rev_tag;
    int add_tag;
    Treap(int _val):L(NULL),R(NULL),min_val(_val),size(1),rev_tag(false),add_tag(0),val(_val){}
    void pull()
    {
        if(L) L->push();
        if(R) R->push();
        size =  (L ? L->size : 0) + (R ? R->size : 0) + 1;
        min_val = min( min( val, L ? L->min_val : INF), R ? R->min_val : INF);
    }
    void push()
    {
        val += add_tag;
        min_val += add_tag;
        if(L) L->add_tag += add_tag;
        if(R) R->add_tag += add_tag;
        add_tag = 0;
        if(rev_tag)
        {
            swap(L,R);
            if(L) L->rev_tag ^= 1;
            if(R) R->rev_tag ^= 1;
            rev_tag = false;
        }
    }
};

inline int Random()
{
    static int x = 7122;
    return (x = x * 0xdefaced + 1) & INF;
}

void split(Treap *p, Treap *&a, Treap *&b, int k)
{
    int sz = p ? p->size : 0;
    if(!p) a = b = NULL;
    else if(k<=0) a = NULL, b = p;
    else
    {
        p->push();
        if(p->L && p->L->size >=k)
        {
            b = p;
            split(p->L, a, b->L, k);
        }
        else
        {
            a = p;
            split(p->R, a->R, b, k - (p->L ? p->L->size : 0) -1 );
        }
        p->pull();
    }
}
Treap* merge(Treap *a, Treap *b)
{
    if(!a) return b;
    if(!b) return a;
    if(Random()%(a->size+b->size) < a->size)
    {
        a->push();
        a->R = merge(a->R,b);
        a->pull();
        return a;
    }
    b->push();
    b->L = merge(a,b->L);
    b->pull();
    return b;
}
void insert(Treap *&p, int x, int pos)
{
    Treap *a, *b;
    Treap *t = new Treap(x);
    split(p,a,b,pos);
    p = merge(merge(a,t),b);
}
void del(Treap *&p, int x)
{
    Treap *a, *b, *c, *d;
    split(p,a,d,x-1);
    split(d,b,c,1);
    p = merge(a,c);
}
void reverse(Treap *&p, int x,int y)
{
    Treap *a, *b ,*c;
    split(p,a,c,y);
    split(a,a,b,x-1);
    b->rev_tag ^= 1;
    p = merge(merge(a,b),c);
}
void add(Treap *&p, int x,int y,int v)
{
    Treap *a, *b ,*c;
    split(p,a,c,y);
    split(a,a,b,x-1);
    b->add_tag += v;
    p = merge(merge(a,b),c);
}
int Min(Treap *&p, int x, int y)
{
    Treap *a, *b, *c;
    split(p,a,c,y);
    split(a,a,b,x-1);
    int ans = b->min_val + b->add_tag;
    p = merge(merge(a,b),c);
    return ans;
}
void revolve(Treap *&p, int x, int y, int t)
{
    Treap *a, *b ,*c, *d ,*e;
    split(p,a,c,y);
    split(a,a,b,x-1);
    split(b,d,e,(y-x+1)-t%(y-x+1));
    p = merge(merge(a,merge(e,d)),c);
}

int main()
{
    int n,m;
    scanf("%d",&n);
    int a[maxn];
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
    Treap* root = new Treap(a[1]);
    for(int i=2; i<=n; i++)
        insert(root,a[i],i);
    scanf("%d",&m);
    while(m--)
    {
        char s[10];
        scanf(" %s",s);
        if(strcmp(s,"ADD")==0)
        {
            int x, y, d;
            scanf("%d%d%d",&x,&y,&d);
            add(root,x,y,d);
        }
        else if(strcmp(s,"REVERSE")==0)
        {
            int x, y;
            scanf("%d%d",&x,&y);
            reverse(root,x,y);
        }
        else if(strcmp(s,"REVOLVE")==0)
        {
            int x, y, t;
            scanf("%d%d%d",&x,&y,&t);
            revolve(root,x,y,t);
        }
        else if(strcmp(s,"INSERT")==0)
        {
            int x, p;
            scanf("%d%d",&x,&p);
            insert(root,p,x);
        }
        else if(strcmp(s,"DELETE")==0)
        {
            int x;
            scanf("%d",&x);
            del(root,x);
        }
        else if(strcmp(s,"MIN")==0)
        {
            int x, y;
            scanf("%d%d",&x,&y);
            printf("%d\n",Min(root,x,y));
        }
    }
    return 0;
}
