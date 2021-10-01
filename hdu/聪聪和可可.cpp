/**
vijos
*/
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
struct edge
{
    int next;
    int ed;
} E[2010];
int Ecnt;
int head[1010];
int wayCnt[2010];
int St,Ed;
int N,M;
//dp data
int nextPos[1010][1010];
double dp[1010][1010];
// SPFA data
int dis[1010][1010];
queue <int> q;
bool inQueue[1010];
// code
void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void SPFA(int st)
{
    while(!q.empty()) q.pop();
    dis[st][st]=0;
    inQueue[st]=true;
    nextPos[st][st]=0x3f3f3f3f;
    q.push(st);
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        inQueue[t]=false;
        for(int i=head[t]; i; i=E[i].next)
        {
            int ed=E[i].ed;
            if(dis[st][t]+1<dis[st][ed])
            {
                dis[st][ed]=dis[st][t]+1;
                if(!inQueue[ed])
                {
                    q.push(ed);
                    inQueue[ed]=true;
                }
                nextPos[st][ed]=(nextPos[st][t]>1e9?ed:nextPos[st][t]);//更新下一步节点
            }
            else if(dis[st][t]+1==dis[st][ed]&&nextPos[st][t]<nextPos[st][ed])
            {
                nextPos[st][ed]=(nextPos[st][t]>1e9?ed:nextPos[st][t]);
            }
        }
    }
}
void init()
{
    scanf("%d%d",&N,&M);
    scanf("%d%d",&St,&Ed);
    for(int i=1; i<=M; ++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y);
        addEdge(y,x);
        wayCnt[x]++;
        wayCnt[y]++;
    }
    memset(dis,0x3f,sizeof(dis));
    memset(dp,-1,sizeof dp);
    for(int i=1; i<=N; ++i)
        SPFA(i);
    /*for(int i=1; i<=N; ++i)
    {
        for(int j=1; j<=N; ++j)
        {
            printf("(%d->%d)=%d ",i,j,nextPos[i][j]);
        }
        puts("");
    }*/
    //for(int i=1;i<=N;++i)
    //    printf("%d\n",wayCnt[i]);
}
double dfs(int st,int ed)
{
    //printf("dfs in %d->%d \n",st,ed);
    if(st==ed)
        return dp[st][ed]=0;
    if(nextPos[st][ed]==ed)
        return dp[st][ed]=1;
    if(nextPos[nextPos[st][ed]][ed]==ed)
        return dp[st][ed]=1;
    if(dp[st][ed]>=0)
        return dp[st][ed];
    int u=nextPos[nextPos[st][ed]][ed];
    double ret=1;//从st到u已经走了一次
    for(int i=head[ed];i;i=E[i].next)
    {
        int v=E[i].ed;
        ret+=dfs(u,v)/(wayCnt[ed]+1);
    }
    ret+=dfs(u,ed)/(wayCnt[ed]+1);//没有动
    //printf("expect %d->%d=%f\n",st,ed,ret);
    return dp[st][ed]=ret;
}
int main()
{
    init();
    printf("%.3f\n",dfs(St,Ed));
    //system("pause");
    return 0;
}