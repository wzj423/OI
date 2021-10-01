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
struct edge {
    int ed,next;
} E[1001000];
int head[300010],Ecnt;
int a[300010];
int depth[300100],fa[300100],size[300100];
int sid[300100],real[300100],scnt;//重编号映射关系
int hson[300100];
int top[300100];
struct node {
    LL atag,sum;
} T[6001000];
int N,M;
int war[300010][2],wcnt;
// code
void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
///two dfs
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
            if(hson[st]==0||size[ed]>size[ hson[st] ])
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
///end of dfs
///seg_tree
void build_tree(int L,int R,int id)
{
    if(L==R)
    {
        T[id].sum=a[real[L]];
        return;
    }
    int mid=(L+R)>>1;
    build_tree(L,mid,id<<1);
    build_tree(mid+1,R,id<<1|1);
    T[id].sum=T[id<<1].sum+T[id<<1|1].sum;
}
void clean_mark(int L,int R,int id)
{
    if(T[id].atag)
    {
        T[id].sum+=T[id].atag*(R-L+1);
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
    if(L>E||R<B)    return;
    clean_mark(L,R,id);
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
}
LL query(int B,int E,int L,int R,int id)
{
    if(L>E||R<B)    return 0;
    clean_mark(L,R,id);
    if(L>=B&&R<=E)
        return T[id].sum;
    int mid=(L+R)>>1;
    return query(B,E,L,mid,id<<1)+query(B,E,mid+1,R,id<<1|1);
}
///end of seg_tree
//tasks
int lca(int x,int y)
{
    while(top[x]!=top[y])
        if(depth[top[x]]>depth[top[y]])     x=fa[top[x]];
        else                                y=fa[top[y]];
    if(depth[x]>depth[y])   return y;
    else                    return x;
}
void node_add()
{
    int x,y;
    scanf("%d%d",&x,&y);
    if(depth[x]<depth[y])
        swap(x,y);
    war[++wcnt][0]=x;
    war[wcnt][1]=y;
    //printf("begin war between %d and %d,add on %d\n",x,y,x);
    modify(sid[x],sid[x],1,1,N,1);
}
void node_del()
{
    int wid,x,y;
    scanf("%d",&wid);
    x=war[wid][0],y=war[wid][1];
    if(depth[x]<depth[y])
        swap(x,y);
    //printf("end war between %d and %d,del on %d\n",x,y,x);
    modify(sid[x],sid[x],-1,1,N,1);
}
void chain_query()
{
    LL ret=0;
    int u,v,tu,tv,tpos;
    scanf("%d%d",&u,&v);
    tu=top[u],tv=top[v];
    tpos=lca(u,v);
    while(tu!=tv)
    {
        if(depth[tu]<depth[tv])
            swap(tu,tv),swap(u,v);
        ret+=query(sid[tu],sid[u],1,N,1);
        //printf("get %lld\n",query(sid[tu],sid[u],1,N,1));
        u=fa[tu];
        tu=top[u];
    }
    if(depth[u]<depth[v])   swap(u,v);
    ret+=query(sid[v],sid[u],1,N,1);
    //printf("get %lld\n",query(sid[v],sid[u],1,N,1));
    ret-=query(sid[tpos],sid[tpos],1,N,1);
    //printf("result=%lld\n",ret);
    if(ret>0)   puts("No");
    else        puts("Yes");
}
//
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1; i<N; ++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y);
        addEdge(y,x);
    }
    depth[1]=1;
    dfs1(1);
    dfs2(1,1);
    build_tree(1,N,1);

    for(int i=1; i<=M; ++i)
    {
        char x;
        scanf("%1s",&x);
        switch (x)
        {
        case 'C':
            node_add();
            break;
        case 'U':
            node_del();
            break;
        case 'Q':
            chain_query();
            break;
        }
    }
    return 0;
}