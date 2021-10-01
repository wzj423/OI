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
int N,M;
struct edge
{
    int ed,next;
}E[100100];
int head[10010],Ecnt;

int dfn[10010],low[10010];
int dfsId;

stack<int> S;
bool vis[10010];

int areaCnt;
int belong[10010],si[10010];
int ans;
// code
void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void init()
{
    int x,y,b;
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;++i)
    {
        scanf("%d%d%d",&x,&y,&b);
        if(x==y)
            continue;
        if(b==1)
            addEdge(x,y);
        else
        {
            addEdge(x,y);
            addEdge(y,x);
        }
    }
}
void dfs(int u)
{
    //printf("dfs in %d\n",u);
    dfn[u]=low[u]=++dfsId;
    S.push(u);
    vis[u]=true;
    for(int i=head[u];i;i=E[i].next)
    {
        int v=E[i].ed;
        if(!dfn[v])
        {
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
    {
        ++areaCnt;
        while(S.top()!=u)
        {
            vis[S.top()]=false;
            belong[S.top()]=areaCnt;
            ++si[areaCnt];
            S.pop();
        }
        vis[S.top()]=false;
        belong[S.top()]=areaCnt;
        ++si[areaCnt];
        S.pop();      
    }
}

void work()
{
    for(int i=1;i<=N;++i)
        if(!dfn[i])
            dfs(i);
    int maxNum=0;
    for(int i=1;i<=N;++i)
        if(si[belong[i]]>maxNum)
        {
            maxNum=si[belong[i]];
            ans=belong[i];
        }
    printf("%d\n",si[ans]);
    for(int i=1;i<=N;++i)
        if(belong[i]==ans)
            printf("%d ",i);
}
int main()
{
    init();
    work();
    return 0;
}