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
int N,M;
struct edge {
    int ed,next,vv;
} E[10010];
int head[3010],Ecnt;

int val[3010];

int dp[3010][3010];
/*
dp[i][j] 第i节点的子树取j个的最大收益
*/
// code
void addEdge(int st,int ed,int vv)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].vv=vv;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void init()
{
    scanf("%d%d",&N,&M);
    for(int i=1; i<=N-M; ++i)
    {
        int k;
        scanf("%d",&k);
        for(int j=1; j<=k; ++j)
        {
            int y,v;
            scanf("%d%d",&y,&v);
            addEdge(i,y,v);
            //printf("%d->%d %d\n",i,y,v);
        }
    }
    for(int i=N-M+1; i<=N; ++i)
        scanf("%d",&val[i]);
}
int dfs(int u)
{
    //printf("dfs in %d\n",u);
    dp[u][0]=0;
    if(u>=N-M+1)
    {
        dp[u][1]=val[u];
        //printf("dp[%d][%d]=%d\n",u,0,dp[u][0]);
        return 1;
    }
    int sum=0;//子树重量
    for(int i=head[u]; i; i=E[i].next)
    {
        int v=E[i].ed;
        int x=dfs(v);
        sum+=x;
        for(int j=sum; j; --j) //01背包倒序
            for(int k=1; k<=x; ++k)
            {
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]-E[i].vv);
                //printf("dp[%d][%d]=    dp[%d][%d](%d)+dp[%d][%d](%d)-%d    %d\n",u,j,u,j-k,dp[u][j-k],v,k,dp[v][k],E[i].vv,dp[u][j]);
            }
    }
    return sum;
}
void work()
{
    memset(dp,0xc0,sizeof dp);
    dfs(1);
    for(int i=M;i>=0;--i)
    {
        if(dp[1][i]>=0)
        {
            printf("%d\n",i);
            break;
        }
    }
}
int main()
{
    init();
    work();
    return 0;
}