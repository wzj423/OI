#include <bits/stdc++.h>

using namespace std;
int N,M;
char opt[30];
const int MAXN=5e4+10;
struct line {
    double k,b;
    int id;
    double getf(int x)
    {
        return k*x+b;
    }
} t[MAXN<<3];
bool cmp(line a,line b,int x) // return whether b>a
{
    if(!a.id)   return true;
    return a.getf(x)<b.getf(x) ? a.getf(x) < b.getf(x) : a.id<b.id;
}
line query(int id,int L,int R,int x){
    if(L==R)    return t[id];
    int mid=(L+R)>>1;
    line tmp;
    if(x<=mid)  tmp=query(id<<1,L,mid,x);
    else        tmp=query(id<<1|1,mid+1,R,x);
    return      cmp(t[id],tmp,x) ? tmp : t[id];
}
void insert(int id,int L,int R,line x) {//to add a line on a specific seg_tree node
    if(!t[id].id)   t[id]=x;
    if(cmp(t[id],x,L))//使得在区间的左端点上,t[id] 比 x要大
        swap(t[id],x);
    if(L==R || t[id].k==x.k)//只有一点,没得比 斜率一样,无焦点,不用比
        return;
    int mid=(L+R)>>1;
    double X=(t[id].b-x.b)/(x.k-t[id].k);//交点横坐标
    if(X<L||X>R)    return;
    if(X<=mid)  insert(id<<1,L,mid,t[id]) , t[id]=x;
    else        insert(id<<1|1,mid+1,R,x);
}
void add(int id,int L,int R,int x,int y,line v) {
    if(x<=L && y>=R) {
        insert(id,L,R,v);
        return;
    }
    int mid=(L+R)>>1;
    if(x<=mid)  add(id<<1,L,mid,x,y,v);
    if(y>mid)   add(id<<1|1,mid+1,R,x,y,v);
}
int main()
{
    scanf("%d",&M);
    N=5e4;
    while(M--) {
        scanf("%s",opt);
        if(opt[0]=='P') {
            line tmp;
            scanf("%lf%lf",&tmp.b,&tmp.k);
            tmp.b-=tmp.k;
            tmp.id=1;
            add(1,1,N,1,N,tmp);
        }
        int x;
        if(opt[0]=='Q'){
            scanf("%d",&x);
            //printf("%lf\n",query(1,1,N,x).getf(x) );
            printf("%lld\n",(long long)(query(1,1,N,x).getf(x) / 100 +1e-8) );
        }
    }
    return 0;
}