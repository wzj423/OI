#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
int N;
const int MAXN=5010,MAXM=10010;
struct node {
    int cnt,len;
} T[MAXM*32];
int Tcnt;
struct data{
    int l,r,y,vv;///segment [L,R]   = range [L,R-1]
}a[MAXN*4];
int acnt;
struct square{
    int x1,y1,x2,y2;
}S[MAXN];
// code
void push_up(int x,int L,int R)
{
    if(T[x].cnt>0)      T[x].len=R-L+1;
    else if(L==R)       T[x].len=0;
    else                T[x].len=T[x<<1].len+T[x<<1|1].len;
}
void modify(int id,int B,int E,int x,int L,int R)///segment [L,R]   = range [L,R-1]
{
    if(L>E||R<B)    return;
    if(L>=B&&R<=E) 
    {
        T[id].cnt+=x;
        push_up(id,L,R);
        return;
    }
    int mid=(L+R)>>1;
    modify(id<<1,B,E,x,L,mid),modify(id<<1|1,B,E,x,mid+1,R);
    push_up(id,L,R);
}
void addSide(int l,int r,int y,int vv)
{
    if(l==r)    return;
    a[++acnt].l=l;
    a[acnt].r=r-1,a[acnt].y=y,a[acnt].vv=vv;
}
bool cmp(data a,data b)
{
    return a.y<b.y;
}
int ans;
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        addSide(x1,x2,y1,1);
        addSide(x1,x2,y2,-1);
        S[i].x1=x1,S[i].y1=y1,S[i].x2=x2,S[i].y2=y2;
    }
    sort(a+1,a+acnt+1,cmp);
    int lastlen=0;
    for(int i=1;i<=acnt;++i)
    {
        modify(1,a[i].l+MAXM,a[i].r+MAXM,a[i].vv,1,2*MAXM+10);
        if(a[i].y!=a[i+1].y)
        {
            ans+=abs(lastlen-T[1].len);
            lastlen=T[1].len;
        }
    }
    acnt=0;
    memset(a,0,sizeof a);
    for(int i=1;i<=N;++i)
    {
        addSide(S[i].y1,S[i].y2,S[i].x1,1);
        addSide(S[i].y1,S[i].y2,S[i].x2,-1);
    }
    sort(a+1,a+acnt+1,cmp);
    lastlen=0;
    for(int i=1;i<=acnt;++i)
    {
        modify(1,a[i].l+MAXM,a[i].r+MAXM,a[i].vv,1,2*MAXM+10);
        if(a[i].y!=a[i+1].y)
        {
            ans+=abs(lastlen-T[1].len);
            lastlen=T[1].len;
        }
    }
    printf("%d\n",ans);
    return 0;
}