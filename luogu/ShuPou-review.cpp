#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include<string>

#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
using namespace std;
typedef long long LL;
LL N,M,Root,Mod;
struct edge{
    LL ed,next;
}E[3*100010];
LL head[100010],Ecnt;

LL ww[100010];
LL hson[100010],top[100010],Size[100010],fa[100010],depth[100010];
LL sid[100010],real[100010],scnt;

struct node{LL sum,tag;}T[800010];
//code
void addEdge(LL st,LL ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
//dfs 
void dfs1(LL st)
{
    Size[st]=1;
    for(LL i=head[st];i;i=E[i].next)
    {
        LL ed=E[i].ed;
        if(ed!=fa[st])
        {
            fa[ed]=st;
            depth[ed]=depth[st]+1;
            dfs1(ed);
            if(hson[st]==0||Size[ed]>Size[hson[st]])
                hson[st]=ed;
            Size[st]+=Size[ed];
        }
    }
}
void dfs2(LL st,LL anc)
{
    top[st]=anc;
    sid[st]=++scnt;
    real[scnt]=st;
    if(hson[st]==0) return ;
    dfs2(hson[st],anc);
    for(LL i=head[st];i;i=E[i].next)
    {
        LL ed=E[i].ed;
        if(ed!=fa[st]&&ed!=hson[st])
            dfs2(ed,ed);
    }    
}
//end of dfs
//seg_tree
void clean_mark(LL L,LL R,LL id)
{
    if(!T[id].tag)  return;
    T[id].sum+=(R-L+1)*T[id].tag;
    if(L!=R)
    {
        T[id<<1].tag+=T[id].tag;
        T[id<<1|1].tag+=T[id].tag;
    }
    T[id].tag=0;
}
void build_tree(LL L,LL R,LL id)
{
    if(L==R)
        T[id].sum=ww[real[L]];
    else
    {
        LL mid=(L+R)>>1;
        build_tree(L,mid,id<<1);
        build_tree(mid+1,R,id<<1|1);
        T[id].sum=T[id<<1].sum+T[id<<1|1].sum;
    }
}
void modify(LL B,LL E,LL x,LL L,LL R,LL id)
{
    if(L>E||R<B)    return;
    clean_mark(L,R,id);
    if(L>=B&&R<=E)
    {
        T[id].tag+=x;
        return;
    }
    LL mid=(L+R)>>1;
    modify(B,E,x,L,mid,id<<1),modify(B,E,x,mid+1,R,id<<1|1);
    clean_mark(L,mid,id<<1),clean_mark(mid+1,R,id<<1|1);
    T[id].sum=T[id<<1].sum+T[id<<1|1].sum;
}
LL  query(LL B,LL E,LL L,LL R,LL id)
{
    if(L>E||R<B)    return 0ll;
    clean_mark(L,R,id);
    if(L>=B&&R<=E)
        return T[id].sum% Mod;
    LL mid=(L+R)>>1;
    return ( query(B,E,L,mid,id<<1)+query(B,E,mid+1,R,id<<1|1) )%Mod;    
}
//end of seg_tree
//tasks
void tree_add()
{
    LL x,v;
    scanf("%lld%lld",&x,&v);
    modify(sid[x],sid[x]+Size[x]-1,v,1,N,1);
}
void tree_query()
{
    LL x;
    scanf("%lld",&x);
    printf("%lld\n",query(sid[x],sid[x]+Size[x]-1,1,N,1)%Mod );
}
void chain_add()
{
    LL u,v,x,tu,tv;
    scanf("%lld%lld%lld",&u,&v,&x);
    tu=top[u],tv=top[v];
    while(tu!=tv)
    {
        if(depth[tu]<depth[tv])
            swap(tu,tv),swap(u,v);
        modify(sid[tu],sid[u],x,1,N,1);
        u=fa[tu];
        tu=top[u];
    }
    if(depth[u]<depth[v])
        swap(u,v);
    modify(sid[v],sid[u],x,1,N,1);
}
void chain_query()
{
    LL u,v,tu,tv;
    LL ret=0;
    scanf("%lld%lld",&u,&v);
    tu=top[u],tv=top[v];
    while(tu!=tv)
    {
        if(depth[tu]<depth[tv])
            swap(tu,tv),swap(u,v);
        ret+=query(sid[tu],sid[u],1,N,1)%Mod;
        u=fa[tu];
        tu=top[u];
    }
    if(depth[u]<depth[v])
        swap(u,v);
    ret+=query(sid[v],sid[u],1,N,1)%Mod;
    printf("%lld\n",ret%Mod);
}
//end of tasks
int main()
{
    scanf("%lld%lld%lld%lld",&N,&M,&Root,&Mod);
    for(LL i=1;i<=N;++i)   scanf("%lld",ww+i);
    for(LL i=1;i<N;++i)
    {
        LL x,y;
        scanf("%lld%lld",&x,&y);
        addEdge(x,y);
        addEdge(y,x);
    }
    dfs1(Root);
    dfs2(Root,Root);
    build_tree(1,N,1);
    for(LL i=1;i<=M;++i)
    {
        LL x;
        scanf("%lld",&x);
        switch(x)
        {
            case 1:chain_add();break;
            case 2:chain_query();break;
            case 3:tree_add();break;
            case 4:tree_query();break;
        }
    }
    return 0;
}