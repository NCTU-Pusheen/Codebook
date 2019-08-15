template<typename T> struct Point
{
    T x,y;
    Point(){}
    Point(const T &x,const T &y):x(x),y(y){}
    inline T dist(Point b) {
        return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
    }
    static bool cmpx(const Point &a,const Point &b) {
        if(a.x==b.x)return a.y<b.y;
        return a.x<b.x;
    }
    static bool cmpy(const Point &a,const Point &b) {
        if(a.y==b.y)return a.x<b.x;
        return a.y<b.y;
    }
};
template<typename T,typename _IT = Point<T>* >
void DC(T &d, _IT p, _IT t, int L, int R) //Divide and Conquer //NlgN
{
    if(L>=R) return;
    int mid = (L+R)>>1;
    DC(d,p,t,L,mid);
    DC(d,p,t,mid+1,R);
    int N = 0;
    for(int i=mid; i>=L && p[mid].x-p[i].x<d; i--) t[N++] = p[i];
    for(int i=mid+1; i<=R && p[i].x-p[mid].x<d; i++) t[N++] = p[i];
    sort(t,t+N,t->cmpy);
    for(int i=0; i<N-1; i++)
        for(int j=1; j<=3 && i+j<N; j++)
            d = min(d,t[i].dist(t[i+j]));
}
template<typename T,typename _IT = Point<T>* >
void closest_pair(T &d,_IT p, _IT t, int n) {
    sort(p,p+n,p->cmpx); DC(d,p,t,0,n-1);
}
int main() {
    Point<double> p[maxn],t[maxn];
    int n; scanf("%d",&n);
    for(int i=0; i<n; i++) scanf("%lf%lf",&p[i].x,&p[i].y);
    double d = INF; closest_pair(d,p,t,n);
    printf("distance = %lf\n",d);
    return 0;
}
