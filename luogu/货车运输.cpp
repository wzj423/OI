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

using namespace std;
const int INF=0x3f3f3f3f;
int N,M,Q;
struct _edge
{
    int vv,x,y;
}t;
bool cmp(_edge a,_edge b) {return a.vv>b.vv;}
vector <_edge> Es;

struct edge
{
    int next,ed,vv;
} E[200010];
int Ecnt,head[10010];

int fa[10100];

//dfs visit
bool vis[10100];

int depth[10100];//节点深度
int f[10100][23];//跳节点目的地
int g[10100][23];//跳节点区间最小值
// code
int gfa(int x) {return fa[x]==0?x:fa[x]=gfa(fa[x]);}
void join(int x,int y) /*uncheck*/ {fa[gfa(x)]=gfa(y);}

void addEdge(int st,int ed,int vv)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    E[Ecnt].vv=vv;
    head[st]=Ecnt;
}

void init()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;++i)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        t.x=x,t.y=y,t.vv=v;
        Es.push_back(t);
    }
    sort(Es.begin(),Es.end(),cmp);
    //kruskal
    for(int i=0;i<M;++i)
    {
        int x=Es[i].x,y=Es[i].y,v=Es[i].vv;
        if(gfa(x)!=gfa(y))
        {
            addEdge(x,y,v);
            addEdge(y,x,v);        
            join(x,y);
        }
    }
}
void dfs(int st)
{
    vis[st]=true;
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed,vv=E[i].vv;
        if(!vis[ed])
        {
            f[ed][0]=st;
            g[ed][0]=vv;
            depth[ed]=depth[st]+1;
            dfs(ed);           
        }
    }
}
void calc_double()
{
    for(int i=1;i<=20;++i)
        for(int j=1;j<=N;++j)
            if(depth[j]>(1<<i))
            {
                f[j][i]=f[ f[j][i-1] ][i-1];
                g[j][i]=min(g[j][i-1],g[ f[j][i-1] ][i-1]);
            }
}
/*int lca(int x,int y)
{
    if(depth[x]<depth[y])
        swap(x,y);
    printf("Dx=%d Dy=%d\n",depth[x],depth[y]);
    int dep=depth[x]-depth[y];
    for(int i=20;i>=0;--i)
        if((1<<i)<=dep)
        {
            printf("%d jumped %d to %d\n",x,(1<<i),f[x][i]);
            x=f[x][i];
            dep-=(1<<i);
        }
    if(x==y)    return x;
    for(int i=20;i>=0;--i)
    {
        if(f[x][i]!=f[y][i])
        {
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}*/
int solve(int x,int y)
{
    int minX=INF,minY=INF;
    if(depth[x]<depth[y])
        swap(x,y);
    int dep=depth[x]-depth[y];
    for(int i=20;i>=0;--i)
        if((1<<i)<=dep)
        {
            minX=min(minX,g[x][i]);
            x=f[x][i];
            dep-=(1<<i);
        }
    if(x==y)    return min(minX,minY);
    for(int i=20;i>=0;--i)
        if(f[x][i]!=f[y][i])
        {
            minX=min(minX,g[x][i]);
            minY=min(minY,g[y][i]);
            x=f[x][i];
            y=f[y][i];
        }
    minX=min(minX,g[x][0]);
    minY=min(minY,g[y][0]);
    x=f[x][0];
    y=f[y][0];
    return min(minX,minY);
}
void work()
{
    depth[1]=1;
    dfs(1);
    calc_double();
//solve
    scanf("%d",&Q);
    for(int i=1;i<=Q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(gfa(x)!=gfa(y))
            puts("-1");
        else
           printf("%d\n",solve(x,y));            
    }
}
int main()
{
    freopen("truck.in","r+",stdin);
    freopen("truck.out","w+",stdout);
    init();
    work();
    return 0;
}