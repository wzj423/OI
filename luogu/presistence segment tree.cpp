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
const int maxn=2*1e5+10;
struct AA{int vv,id;}a[maxn];
struct node{
    int l,r,sum;
}T[maxn<<6];
int Tcnt;
int Root[maxn],Rank[maxn];
int N,M;
// code
bool cmp(AA x,AA y)
{
    return x.vv<y.vv;
}
//fseg_tree
void insert(int x,int &id,int l,int r)//只有需要新建的节点会执行插入操作
{
    T[++Tcnt]=T[id];
    id=Tcnt;//新建节点并复制
    ++T[id].sum;
    int mid=(l+r)>>1;
    if(l==r)    return;
    if(x<=mid)  insert(x,T[id].l,l,mid);
    else        insert(x,T[id].r,mid+1,r);
}
int query(int B_id,int E_id,int k,int l,int r)//查询[B+1,E]  = (B,E]
{
    if(l==r)    return l;
    int t=T[ T[E_id].l ].sum-T[ T[B_id].l ].sum;
    int mid=(l+r)>>1;

    if(k<=t)    return query(T[B_id].l,T[E_id].l,k,l,mid);
    else        return query(T[B_id].r,T[E_id].r,k-t,mid+1,r);
}
//end of fseg_tree
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)   scanf("%d",&a[i].vv),a[i].id=i;
    sort(a+1,a+N+1,cmp);
    for(int i=1;i<=N;++i)   Rank[a[i].id]=i;

    for(int i=1;i<=N;++i)
    {
        Root[i]=Root[i-1];
        insert(Rank[i],Root[i],1,N);
    }
    for(int i=1;i<=M;++i)
    {
        int L,R,K,Ret;
        scanf("%d%d%d",&L,&R,&K);
        Ret=query(Root[L-1],Root[R],K,1,N);
        printf("%d\n",a[Ret].vv);
    }
    return 0;
}