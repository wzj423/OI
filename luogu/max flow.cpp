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
struct edge{int ed,next;}E[1001000];
int head[50010],Ecnt;
int a[50010];
int tag[50010];
int fa[50100][21];
int depth[50100];
int N,K;
int ans=0;
// code
void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void dfs(int st,int deep)
{
    depth[st]=deep;
    for(int j=1;j<=20;++j)
        if(fa[ fa[st][j-1] ][j-1])
            fa[st][j]=fa[ fa[st][j-1] ][j-1];
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed;
        if(ed!=fa[st][0])
        {
            fa[ed][0]=st;
            dfs(ed,deep+1);
        }
    }
}
void dfs2(int st)
{
    //if(fa[st][0])
     //   a[st]=a[ fa[st][0] ]+tag[st];
    a[st]=tag[st];
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed;
        if(ed!=fa[st][0])
        {
            dfs2(ed);          
            a[st]+=a[ed];  
        }
    }
    ans=max(ans,a[st]);
}
int lca(int x,int y)
{
    if(depth[x]<depth[y])
        swap(x,y);
    int t=depth[x]-depth[y];
    for(int i=20;i>=0;--i)
        if((1<<i)<=t)
        {
            t-=(1<<i);
            x=fa[x][i];
        }
    for(int i=20;i>=0;--i)
        if(fa[x][i]!=fa[y][i])
        {
            x=fa[x][i],y=fa[y][i];
        }
    if(x==y)    return x;
    else return fa[x][0];
}
int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1;i<N;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y);
        addEdge(y,x);
    }
    dfs(1,1);
    for(int i=1;i<=K;++i)
    {
        int x,y,top;
        scanf("%d%d",&x,&y);
        top=lca(x,y);
        tag[x]+=1;
        tag[y]+=1;
        tag[top]-=1;
        tag[fa[top][0]]-=1;
    }
    dfs2(1);
    printf("%d\n",ans);
    return 0;
}