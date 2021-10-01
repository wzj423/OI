#include <bits/stdc++.h>
#define For(i,a,b) for(register int i=a;i<=b;++i)
const int MAXN=300010,INF=0x3f3f3f3f;
using namespace std;
//hint===============================
/**
起点位于该子树内 dep[St[i]] = dep[j]+W[j]
终点位于该子树内 Ti[i] 时刻 到达 W[Ed[i]]
               Ti[i] - (dep[Ed[i]] - dep[j]) 时刻到达 j
               Ti[i] -dep[Ed[i]] +N = W[j] - dep[j] +N 
*/
//tool==============================
inline int rd() {
    int x=0,f=1;char ch = getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
//data================================
int N,M,W[MAXN],St[MAXN],Ed[MAXN];
int Ti[MAXN];//时间
int fa[MAXN][22];//lca 数据
int dep[MAXN];
int ans[MAXN];//answer
//tree================================
struct edge {
    int ed,next;
}E[MAXN*4];
int head[MAXN],Ecnt;
void addEdge(int st,int ed) {
    E[++Ecnt]=edge{ed,head[st]},head[st]=Ecnt;
}
//lca==================================
namespace LCA{
    void dfs(int u) {
        for(int i=1;i<=20;++i)
            fa[u][i]=fa[ fa[u][i-1] ][i-1];
        for(int i=head[u];i;i=E[i].next) {
            int v=E[i].ed;
            if(v!=fa[u][0]) {
                fa[v][0]=u;
                dep[v]=dep[u]+1;
                dfs(v);
            }
        }
    }
    int lca(int x,int y) {
        if(dep[x]<dep[y])   swap(x,y);
        for(int i=20;i>=0;--i)
            if(dep[ fa[x][i] ] >= dep[y]) x=fa[x][i];
        if(x==y)    return x;
        for(int i=20;i>=0;--i)
            if(fa[x][i]!=fa[y][i])
                x=fa[x][i],y=fa[y][i];
        return fa[x][0];
    }
}
//segment_tree=============================
int sum[MAXN*12*10],lc[MAXN*12*10],rc[MAXN*12*10];
int cnt;
int tree1[MAXN],tree2[MAXN];//tree1处理St,tree2处理Ed
void insert(int &x,int pos,int vv,int L=1,int R=3*N) {//记得加offset

    if(!x)  x=++cnt;
//printf("insert in [%d,%d] x=%d\n",L,R,x);
//system("pause");
    sum[x]+=vv;
    if(L==R)    return;    
    int mid=(L+R)>>1;
    if(pos<=mid)    insert(lc[x],pos,vv,L,mid);
    else            insert(rc[x],pos,vv,mid+1,R);
}
int query(int x,int pos,int L=1,int R=3*N) {
//printf("query in [%d,%d] x=%d\n",L,R,x);
    if(L==R || !x)    return sum[x];
    int mid=(L+R)>>1;
    if(pos<=mid)  return query(lc[x],pos,L,mid);
    else        return query(rc[x],pos,mid+1,R);
}
int merge(int u,int v) {//线段树合并,把v合并到u上
    if(!u)  return v;
    if(!v)  return u;
    sum[u]+=sum[v];
    lc[u]=merge(lc[u],lc[v]);
    rc[u]=merge(rc[u],rc[v]);
    return u;
}
//final dfs======================================
void debug(int root) {
    printf("Root=%d\n",root);
    for(int i=1;i<=3*N;++i)
        printf("%d ",query(root,i));
    puts("");
}
void dfs(int st) {
    for(int i=head[st];i;i=E[i].next) {
        int ed=E[i].ed;
        if(ed!=fa[st][0]) {
            dfs(ed);
            tree1[st]=merge(tree1[st],tree1[ed]);
            tree2[st]=merge(tree2[st],tree2[ed]);
        }
    }
    ans[st]+=query(tree1[st],dep[st]+W[st]);
    ans[st]+=query(tree2[st],W[st]-dep[st]+N);
}
//main==================================
int main() {
    N=rd(),M=rd();
    For(i,1,N-1) {
        int x=rd(),y=rd();
        addEdge(x,y),addEdge(y,x);
    }
    For(i,1,N)  W[i]=rd();
    For(i,1,M)  St[i]=rd(),Ed[i]=rd();

    dep[1]=1;
    LCA::dfs(1);

    For(i,1,M) {
        int t=LCA::lca(St[i],Ed[i]),ft=fa[t][0];
        Ti[i]=dep[St[i]]+dep[Ed[i]]-2*dep[t];
        //打标记
        /*
        起点位于该子树内 dep[St[i]] = dep[j]+W[j]
        终点位于该子树内 Ti[i] -dep[Ed[i]] +N = W[j] - dep[j] +N 
        */
        insert(tree1[St[i]],dep[St[i]],1);
        insert(tree1[ft],dep[St[i]],-1);
        insert(tree2[Ed[i]],Ti[i] -dep[Ed[i]] +N ,1);
        insert(tree2[t], Ti[i]- dep[ Ed[i] ] +N ,-1);
    }
    dfs(1);
    For(i,1,N)  printf("%d ",ans[i]);
    return 0;
}