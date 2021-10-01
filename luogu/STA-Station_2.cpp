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
const int MAXN=1e6+10;
typedef long long LL;
struct edge{int ed,next;}E[3*MAXN];
int head[MAXN],Ecnt;
int N;
int fa[MAXN];
LL size[MAXN];//以1为根时子树大小
LL f[MAXN];//以1为根时深度之和
LL g[MAXN];//以自身为根时深度之和
/*
f[i]=sigma{ f[chd of i]+size[chd of i] }
g[1]=f[1]
g[i]=g[dad i]-f[i]-size[i] +(size[1]-size[i])+f[i]
    =g[dad i]+size[1]-2*size[i]
*/
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
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed;
        if(ed!=fa[st])
        {
            fa[ed]=st;
            dfs1(ed);
            size[st]+=size[ed];
            f[st]+= f[ed]+size[ed];
        }
    }
    //printf("id=%d size=%d f=%d\n",st,size[st],f[st]);
}
void dfs2(int st)
{
    if(!fa[st]) g[st]=f[st];
    else    g[st]=g[fa[st]]+size[1]-2*size[st];
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed;
        if(ed!=fa[st])
            dfs2(ed);
    }
    //printf("id=%d g=%d\n",st,g[st]);
}
int main()
{
    scanf("%d",&N);
    for(int i=1;i<N;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y);addEdge(y,x);
    }
    dfs1(1);
    dfs2(1);
    int ans=0;
    for(int i=1;i<=N;++i)
        if(g[i]>g[ans])
            ans=i;
    printf("%d\n",ans);
    return 0;
}