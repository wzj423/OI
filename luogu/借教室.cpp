/**
借教室
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
const int INF=0x3f3f3f3f;
const int MAXV=310;
const int MAXE=90010;
const int MAXN=2010;
const int MAXM=2010;
// const&typedef&def
double dis[MAXV][MAXV];
// map

int N,M,V,E;
int a[MAXN];
int b[MAXN];
double chance[MAXN];
// dp
double dp[MAXN][MAXM][2];
/**
dp[i][j][0-1]代表前i门课里选j门进行替换,其中第i门课替换或不替换(0-1)的期望总值
dp[i][j][0]=min{
            dp[i-1][j][0]+dis[a[i-1]][a[i]],
            (dp[i-1][j][1]+dis[b[i-1]][a[i]])*chance[i-1]+
                dis[a[i-1]][a[i]]*(1-chance[i-1])
            }
dp[i][j][1]=min{
            (dp[i-1][j-1][0]+dis[a[i-1]][b[i]])*(chance[i])
                            +dis[a[i-1]][a[i]])*(1-chance[i]),
            dp[i-1][j-1][1]+dis[a[i-1]][a[i]]*(1-chance[i-1])*(1-chance[i]),
                            +dis[a[i-1]][b[i]]*(1-chance[i-1])*chance[i]
                            +dis[b[i-1]][a[i]]*chance[i-1]*(1-chance[i])
                            +dis[b[i-1]][b[i]]*chance[i-1]*chance[i]
                }
dp[i][0][0]=dp[i-1][0][0]+dis[a[i-1]][a[i]]

*/
// code
void addEdge(int x,int y,double vv)
{
    if(x==y)
        return;
    //printf("(%d,%d) dis:%.2f\n",x,y,dis[x][y]);
    if(vv<dis[x][y])
        dis[x][y]=dis[y][x]=vv;
    //printf("vv:%.2f dis:%.2f\n",vv,dis[x][y]);
}
void floyd()
{
    for(int k=1; k<=V; ++k)
        for(int i=1; i<=V; ++i)
            for(int j=1; j<=V; ++j)
                if(dis[i][k]+dis[k][j]<dis[i][j])
                    dis[i][j]=dis[i][k]+dis[k][j];
}
void init()
{
    scanf("%d%d%d%d",&N,&M,&V,&E);
    for(int i=1; i<=V; ++i)
        for(int j=1; j<=V; ++j)
        {
            if(i==j)
                dis[i][j]=0.0;
            else
                dis[i][j]=1e9;
            //printf("%.2f\n",dis[i][j]);
        }
    for(int i=0; i<=N; ++i)
        for(int j=0; j<=M; ++j)
            dp[i][j][0]=dp[i][j][1]=1e9;
    dp[1][0][0]=dp[1][1][1]=0;
    for(int i=1; i<=N; ++i)
        scanf("%d",&a[i]);
    for(int i=1; i<=N; ++i)
        scanf("%d",&b[i]);
    for(int i=1; i<=N; ++i)
    {
        cin>>chance[i];
    }
    int x,y,vv;
    for(int i=1; i<=E; ++i)
    {
        scanf("%d%d%d",&x,&y,&vv);
        addEdge(x,y,vv);
    }

    floyd();
    //printf("%d->%d=%.2f\n",2,1,dis[2][1]);
    //printf("%d->%d=%.2f\n",2,2,dis[2][2]);
}
void work()
{
    for(int i=2; i<=N; ++i)
    {
        dp[i][0][0]=dp[i-1][0][0]+dis[a[i-1]][a[i]];
        for(int j=1; j<=min(M,i); ++j)
        {
            dp[i][j][0]=min(
                            dp[i-1][j][0]+dis[a[i-1]][a[i]],
                            dp[i-1][j][1]
                            +dis[b[i-1]][a[i]]*chance[i-1]
                            +dis[a[i-1]][a[i]]*(1.0-chance[i-1])
                        );
            dp[i][j][1]=min(
                            dp[i-1][j-1][0]
                              +dis[a[i-1]][b[i]]*chance[i]
                              +dis[a[i-1]][a[i]]*(1.0-chance[i]),
                            dp[i-1][j-1][1]
                              +dis[a[i-1]][a[i]]*(1.0-chance[i-1])*(1.0-chance[i])
                              +dis[a[i-1]][b[i]]*(1.0-chance[i-1])*chance[i]
                              +dis[b[i-1]][a[i]]*chance[i-1]*(1.0-chance[i])
                              +dis[b[i-1]][b[i]]*chance[i-1]*chance[i]
                        );

            //printf("%.2f %.2f\n",dp[i][j][0],dp[i][j][1]);
        }
    }
    double ans=dp[N][0][0];
    for(int i=1; i<=M; ++i)
    {
        ans=min(ans,min(dp[N][i][0],dp[N][i][1]));

    }
    printf("%.2f\n",ans);
}
int main()
{
    init();
    work();
    //system("pause");
    return 0;
}