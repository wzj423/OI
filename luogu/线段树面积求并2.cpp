/**
线段树面积求并
codevs3044
*/
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
struct edge
{
    double lx,rx,y;
    int flag;
} E[2010];
double Hash[2010];
struct node
{
    int color;
    double sum;
} T[2010];
// code
/**
Hint:
区间树转化成点树的做法:
如图:
*----------*-----------*------*
1.1        2.2         3.3    4.5
离散化:
*----*----*----*
1   2     3    4
一个节点管一个左开右闭区间:
[*----]
就有了:
[*---][*---][*---][*---]
1      2     3     4
*/
bool cmp(edge a,edge b) 
{
    return a.y<b.y;
}
void init()
{
    memset(T,0,sizeof T);
    memset(E,0,sizeof E);
    memset(Hash,0,sizeof Hash);
}
void pushup(int id,int L,int R)//没有pushdown(标记永久化)
{
    if(T[id].color>0)
        T[id].sum=Hash[R+1]-Hash[L];//因为这里R是最后一个左开右闭区间的左节点,所以还要再+1(向前跳一个节点)
    else if(L==R)
        T[id].sum=0;
    else
        T[id].sum=T[id<<1].sum+T[id<<1|1].sum;
}
void modify(int B,int E,int flag,int L,int R,int id)//[B,E]修改区间,[L,R]当前节点管辖区间
{
    if(L<=B&&R>=E)
    {
        T[id].color+=flag;
        pushup(id,L,R);
        return;
    }
    int mid=(L+R)>>1;
    if(B<=mid)  modify(B,E,flag,L,mid,id<<1);
    if(mid+1<=E) modify(B,E,flag,mid+1,R,id<<1|1);
    pushup(id,L,R);

}
void work()
{
    int x1,x2,y1, y2;
    for(int i=1; i<=N; ++i)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        E[2*i-1].lx=E[2*i].lx=x1;
        E[2*i-1].rx=E[2*i].rx=x2;
        E[2*i-1].y=y1;
        E[2*i].y=y2;
        E[2*i-1].flag=1;
        E[2*i].flag=-1;
        Hash[2*i-1]=x1;
        Hash[2*i+1]=x2;
    }
    sort(E+1,E+2*N+1,cmp);
    sort(Hash+1,Hash+2*N+1);
    double ans=0;

}
int main()
{
    scanf("%d",&N);
    while(N)
    {
        init();
        work();
        scanf("%d",&N);
    }
    return 0;
}