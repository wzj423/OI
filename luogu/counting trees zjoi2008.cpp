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
typedef long long LL;
const int MAXN=30010;
const LL INF=0x3f3f3f3f;
struct edge {
    int ed,next;
} E[300100];
int head[30010],Ecnt;
LL a[30010];
int N,Q;
char command[30];
//data for 树剖
int fa[MAXN],depth[MAXN],hson[MAXN],size[MAXN];
int sid[MAXN],real[MAXN],scnt;
int top[MAXN];
//data for seg_tree
struct node {
    LL atag,sum,max;
} T[500100];
// code
void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void dfs1(int st)
{
    size[st]=1;
    for(int i=head[st]; i; i=E[i].next)
    {
        int ed=E[i].ed;
        if(ed!=fa[st])
        {
            fa[ed]=st;
            depth[ed]=depth[st]+1;
            dfs1(ed);
            if(hson[st]==0||size[ed]>size[hson[st]])
                hson[st]=ed;
            size[st]+=size[ed];
        }
    }
}
void dfs2(int st,int anc)
{
    top[st]=anc;
    sid[st]=++scnt;
    real[scnt]=st;
    if(hson[st]==0) return;
    dfs2(hson[st],anc);
    for(int i=head[st]; i; i=E[i].next)
    {
        int ed=E[i].ed;
        if(ed!=fa[st]&&ed!=hson[st])
            dfs2(ed,ed);
    }
}
//seg_tree
void build_tree(int L,int R,int id)
{
    if(L==R)
        T[id].max=T[id].sum=a[real[L]];
    else
    {
        int mid=(L+R)>>1;
        build_tree(L,mid,id<<1);
        build_tree(mid+1,R,id<<1|1);
        T[id].sum=T[id<<1].sum+T[id<<1|1].sum;
        T[id].max=max(T[id<<1].max,T[id<<1|1].max);
    }
}
void clean_mark(int L,int R,int id)
{
    if(T[id].atag)
    {
        T[id].sum+=(R-L+1)*T[id].atag;
        T[id].max+=T[id].atag;
        if(L!=R)
        {
            T[id<<1].atag+=T[id].atag;
            T[id<<1|1].atag+=T[id].atag;
        }
        T[id].atag=0;
    }
}
void modify(int B,int E,int x,int L,int R,int id)
{
    clean_mark(L,R,id);
    if(L>E||R<B)    return;
    if(L>=B&&R<=E)
    {
        T[id].atag+=x;
        return;
    }
    int mid=(L+R)>>1;
    modify(B,E,x,L,mid,id<<1);
    modify(B,E,x,mid+1,R,id<<1|1);
    clean_mark(L,mid,id<<1);
    clean_mark(mid+1,R,id<<1|1);
    T[id].sum=T[id<<1].sum+T[id<<1|1].sum;
    T[id].max=max(T[id<<1].max,T[id<<1|1].max);
}
LL query_sum(int B,int E,int L,int R,int id)
{
    clean_mark(L,R,id);
    if(L>E||R<B)    return 0;
    if(L>=B&&R<=E)  return T[id].sum;
    int mid=(L+R)>>1;
    return query_sum(B,E,L,mid,id<<1)+query_sum(B,E,mid+1,R,id<<1|1);
}
LL query_max(int B,int E,int L,int R,int id)
{
    clean_mark(L,R,id);
    if(L>E||R<B)    return -INF;
    if(L>=B&&R<=E)  return T[id].max;
    int mid=(L+R)>>1;
    return max( query_max(B,E,L,mid,id<<1) , query_max(B,E,mid+1,R,id<<1|1) ); 
}
//end of seg_tree
//tasks
void node_add()
{
    int x,t;
    scanf("%d%d",&x,&t);
    LL vv=t - query_sum(sid[x],sid[x],1,N,1);
    modify(sid[x],sid[x],vv,1,N,1);
}
void chain_sum()
{
    int u,v,tu,tv;
    LL ret=0;
    scanf("%d%d",&u,&v);
    tu=top[u],tv=top[v];
    while(tu!=tv)
    {
        if(depth[tu]<depth[tv])
            swap(tu,tv),swap(u,v);
        ret+=query_sum(sid[tu],sid[u],1,N,1);
        //printf("sum [%d,%d]=%lld\n",tu,u,query_sum(sid[tu],sid[u],1,N,1));
        u=fa[tu];
        tu=top[u];
    }
    if(depth[u]<depth[v])   swap(u,v);
    ret+=query_sum(sid[v],sid[u],1,N,1);
    //printf("sum [%d,%d]=%lld\n",v,u,query_sum(sid[v],sid[u],1,N,1));
    printf("%lld\n",ret);
}
void chain_max()
{
    int u,v,tu,tv;
    LL ret=-INF;
    scanf("%d%d",&u,&v);
    tu=top[u],tv=top[v];
    while(tu!=tv)
    {
        if(depth[tu]<depth[tv])
            swap(tu,tv),swap(u,v);
        ret=max(ret, query_max(sid[tu],sid[u],1,N,1) );
        //printf("max [%d,%d]=%lld\n",tu,u,query_max(sid[tu],sid[u],1,N,1));
        u=fa[tu];
        tu=top[u];
    }
    if(depth[u]<depth[v])   swap(u,v);
    ret=max(ret , query_max(sid[v],sid[u],1,N,1));
    //printf("max [%d,%d]=%lld\n",v,u,query_max(sid[v],sid[u],1,N,1));
    printf("%lld\n",ret);
}
//
int main()
{
    scanf("%d",&N);
    for(int i=1; i<N; ++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y),addEdge(y,x);
    }
    for(int i=1; i<=N; ++i)
        scanf("%lld",a+i);

    depth[1]=1;
    dfs1(1);
    dfs2(1,1);
    build_tree(1,N,1);

    scanf("%d",&Q);
    for(int i=1;i<=Q;++i)
    {
        scanf("%s",command);
        switch(command[1])
        {
            case 'M':chain_max();break;
            case 'S':chain_sum();break;
            case 'H':node_add();break;
        }
    }
    return 0;
}