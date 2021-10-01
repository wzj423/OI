#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <utility>
#include <queue>
#include <stack>

using namespace std;
typedef long long LL;
const LL INF=0x3f3f3f3f;
int N,K,T,ans;
struct egde{int ed,next;}E[1000010];
int head[100010],Ecnt;
int depth[100010],fa[100010];
pair<int,int> Q[100010];
int vis[100010];
// code
void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void dfs1(int st)
{
    Q[st].first=depth[st];
    Q[st].second=st;
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed;
        if(ed!=fa[st])
        {
            fa[ed]=st;
            depth[ed]=depth[st]+1;
            dfs1(ed);
        }
    }
}
void dfs2(int st,int deep)
{
    if(deep>K)  return;
    vis[st]=true;
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed;
        dfs2(ed,deep+1);
    }
}
int main()
{
    scanf("%d%d%d",&N,&K,&T);
    for(int i=1;i<N;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y);
        addEdge(y,x);
    }
    depth[1]=1;
    dfs1(1);
    sort(Q+1,Q+N+1,greater<pair<int,int> >());
    //for(int i=1;i<=N;++i)
    //{
    //    printf("id=%d depth=%d\n",Q[i].second,Q[i].first);
    //}
    for(int i=1;i<=N;++i)
    {
        if(vis[Q[i].second])    continue;
        int cur=Q[i].second;
        for(int i=1;i<=K;++i)
            cur=fa[cur];
        //printf("to cover %d,set in %d\n",Q[i].second,cur);
        if(cur!=0)  dfs2(cur,0);
        else dfs2(1,0);
        ++ans;
    }
    printf("%d\n",ans);
    return 0;
}