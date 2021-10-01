/**
飞扬的小鸟

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
typedef long long LL;
int N,M,K;
int lift[10010];
int fall[10010];

int obstacle[10010][2];///横坐标为i时候的障碍上界0与下界1
int dp[10010][1010];
///code
void init()
{
    ///freopen("birda.in","r+",stdin);
    ///freopen("birda.out","w+",stdout);
    memset(obstacle,-1,sizeof(obstacle));
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d%d",&lift[i-1],&fall[i-1]);
    }
    int t;
    for(int i=1; i<=K; ++i)
    {
        scanf("%d",&t);
        scanf("%d%d",&obstacle[t][1],&obstacle[t][0]);
        if(obstacle[t][0]<obstacle[t][1])
            swap(obstacle[t][0],obstacle[t][1]);
    }
}
void work()
{
    memset(dp,0x3f,sizeof(dp));
    for(int i=1; i<=M; ++i)
    {
        dp[0][i]=0;
    }
    for(int i=1; i<=N; ++i)
    {
        bool passCurLine=false;
        for(int j=1; j<=M; ++j)
            if(j-lift[i-1]>0)
                dp[i][j]=min(dp[i][j],min(dp[i-1][j-lift[i-1]],dp[i][j-lift[i-1]])+1);

        for(int j=1; j<=M; ++j)
            if(j+fall[i-1]<=M)
                dp[i][j]=min(dp[i][j],dp[i-1][j+fall[i-1]]);

        if(obstacle[i][0]==-1)
            for(int k=M; k>=max(1,M-lift[i-1]); --k)
                dp[i][M]=min(dp[i][M],min(dp[i-1][k],dp[i][k])+1);

        for(int j=1;j<=M;++j)
        {
            if(obstacle[i][0]!=-1&&(obstacle[i][0]<=j||obstacle[i][1]>=j))
                dp[i][j]=0x3f3f3f3f;
            if(dp[i][j]<1e9)
                passCurLine=true;
        }
        if(!passCurLine)
        {
            puts("0");
            int ans=0;
            for(int u=0; u<i; ++u)
                if(obstacle[u][0]!=-1)
                    ++ans;
            printf("%d",ans);
            exit(0);
        }
    }
    puts("1");
    int ans=0x3f3f3f3f;
    for(int i=1; i<=M; ++i)
        ans=min(ans,dp[N][i]);
    printf("%d\n",ans);
}
int main()
{
    init();
    work();
    return 0;
}

