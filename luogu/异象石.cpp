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
struct edge {
    int next,ed,vv;
} E[500000];
int Ecnt,head[100010];
bool own[100010];
int N,M;

int fa[100010][25];
int depth[100010];
int rdis[100010];
int ownpos[100010],ocnt;
// code
void dfs(int st)
{
    for(int i=1;i<=24;++i)
        if(depth[st]>=(1<<i))
            fa[st][i]= fa[ fa[st][i-1] ][i-1];
        else break;
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed;
        if(ed!=fa[st][0])
        {
            fa[ed][0]=st;
            depth[ed]=depth[st]+1;
            rdis[ed]=rdis[st]+E[i].vv;
            dfs(ed);
        }
    }
}
int lca(int x,int y)
{
    if(depth[x]<depth[y])
        swap(x,y);
    int t=depth[x]-depth[y];
    for(int i=0;i<=24;++i)
        if(t&(1<<i))
            x=fa[x][i];
    for(int i=24;i>=0;--i)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i] , y=fa[y][i];
    if(x==y)    return x;
    else    return fa[x][0];
}
void addEdge(int st,int ed,int vv)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].vv=vv;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
int dis(int x,int y)
{
    return rdis[x]+rdis[y]-2*rdis[lca(x,y)];
}
void work1()
{
    char ch;
    int x;
    for(int i=1; i<=M; ++i)
    {
        scanf("%1s",&ch);
        if(ch=='+')
            scanf("%d",&x),own[x]=true;
        else if(ch=='-')
            scanf("%d",&x),own[x]=false;
        else
        {
            int ans=0;
            ocnt=0;
            for(int i=1; i<=N; ++i)
                if(own[i]) 
                {
                    ownpos[++ocnt]=i;
                    if(ocnt>1)
                    {
                        ans+=dis(ownpos[ocnt],ownpos[ocnt-1]);
                    }
                }
            ans+=dis(ownpos[ocnt],ownpos[1]);
            printf("%d\n",ans/2);
        }
    }
}
int main()
{
    scanf("%d",&N);
    for(int i=1; i<N; ++i)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        addEdge(x,y,v);
        addEdge(y,x,v);
    }
    dfs(1);
    scanf("%d",&M);
    if(N<=1050&&M<=1050)
        work1();
    return 0;
}