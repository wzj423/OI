#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=8e5,INF=0x3f3f3f3f;
//defs===================================
int N,M;
typedef set<int>::iterator Iter;
//edge====================================
struct edge {
    int ed,nxt,vv;
} E[3*MAXN];
int head[MAXN],Ecnt;
void addEdge(int st,int ed,int vv) {
    E[++Ecnt]=edge{ed,head[st],vv};
    head[st]=Ecnt;
}
int dfsid,dfn[MAXN],fa[MAXN],depth[MAXN];
ll dis[MAXN];
int rid[MAXN];
int par[MAXN][20];
void dfs(int st) {
    for(int i=1;i<20;++i)
        par[st][i]=par[ par[st][i-1] ][i-1];
    dfn[st]=++dfsid;rid[dfsid]=st;
    for(int i=head[st]; i; i=E[i].nxt) {
        int ed=E[i].ed,vv=E[i].vv;
        if(ed!=fa[st]) {
			fa[ed]=st,dis[ed]=dis[st]+vv,depth[ed]=depth[st]+1,par[ed][0]=st;
			dfs(ed);
        }
    }
}
int lca(int x,int y) {
    if(depth[x]<depth[y]) swap(x,y);
    for(int i=19;i>=0;--i) if(depth[par[x][i]]>=depth[y]) x=par[x][i];
    for(int i=19;i>=0;--i) if(par[x][i]!=par[y][i]) x=par[x][i],y=par[y][i];
    if(x==y) return x;
    else    return par[x][0];
}
ll dist(int x,int y) {
    if(x>1e9||x<-1e9||y>1e9||y<-1e9) return 0;
    x=rid[x],y=rid[y];
    if(x>1e9||x<-1e9||y>1e9||y<-1e9) return 0;
    return dis[x]+dis[y]-2*dis[lca(x,y)];
}
set<int> S;
bool vis[MAXN];
ll ans;
void edit_chain(ll flag) {
    Iter l=S.begin();++l;
    Iter r=S.end();--r,--r;
    ans+=flag*dist(*l,*r);
}
//main==================================
int main() {
    freopen("E:\\lydsy\\3991\\1.in","r",stdin);
    freopen("E:\\lydsy\\3991\\my.out","w",stdout);
    scanf("%d%d",&N,&M);
    for(int i=1;i<N;++i) {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        addEdge(x,y,v),addEdge(y,x,v);
    }
    depth[1]=1;
    dfs(1);
    S.insert(INF),S.insert(-INF);
    Iter pre,nxt,cur;
    for(int i=1;i<=M;++i) {
        int x;
        scanf("%d",&x);
        edit_chain(-1);
        if(!vis[x]) {
            pre=S.lower_bound(dfn[x]);nxt=pre;--pre;
            ans-=dist(*pre,*nxt);
            ans+=dist(*pre,dfn[x]);
            ans+=dist(dfn[x],*nxt);
            S.insert(dfn[x]);
        } else {
            pre=nxt=cur=S.lower_bound(dfn[x]);pre=cur,nxt=cur;--pre,++nxt;
            ans-=dist(*pre,*cur);
            ans-=dist(*cur,*nxt);
            ans+=dist(*pre,*nxt);
            S.erase(cur);
        }
        vis[x]^=1;
        edit_chain(1);
        printf("%lld\n",ans);
    }
    return 0;
}
