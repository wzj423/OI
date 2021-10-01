/**
关路灯
Luogu P1220
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
int N,st;
int pos[60];//位置
int power[60];//功率
int totPower;
int dp[60][60][2];
int help[60][60];
#define MIN(i,j,k) (min(i,min(j,k)))
/*
dp[i][j][0]表示[i,j]区间内的路灯全被关闭时在i号路灯下耗能最小
dp[i][j][1]表示[i,j]区间内的路灯全被关闭时在j号路灯下耗能最小
辅助方程:
    help[i][j]表示[i,j]区间内的路灯被关闭时路灯的总功率;
初始:
    dp[st][st][0]=0;
    dp[st][st][1]=0;
递推方程:
    dp[i][j][0]=min(dp[i+1][j][0]+(pos[i+1]-pos[i])*help[i+1][j],
                    dp[i+1][j][1]+(pos[j]-pos[i])*help[i+1][j]
                    )
    dp[i][j][1]=min(dp[i][j-1][0]+(pos[j]-pos[i])*help[i][j-1],
                    dp[i][j-1][1]+(pos[j]-pos[j-1])*help[i][j-1]
                    )
*/
// code
void init()
{
    memset(dp,0x3f,sizeof(dp));

    scanf("%d%d",&N,&st);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d%d",&pos[i],&power[i]);
        totPower+=power[i];
    }
    dp[st][st][0]=dp[st][st][1]=0;
}
void preCalc()
{
    for(int i=1; i<=N; ++i)
    {
        help[i][i]=totPower-power[i];
    }
    for(int i=1; i<=N; ++i)
    {
        for(int step=2; i+step-1<=N; ++step)
        {
            help[i][i+step-1]=help[i][i+step-2]+help[i+step-1][i+step-1]-totPower;
            //cout<<help[i][i+step-1]<<" ";
        }
        //cout<<endl;
    }
    if(0)for(int i=1; i<=N; ++i)
    {
        for(int step=1; i+step-1<=N; ++step)
        {
            cout<<help[i][i+step-1]<<" ";
        }
        cout<<endl;
    }
}
void work()
{
    for(int i=st; i>=1; i--)
        for(int j=i+1; j<=N; j++)
        {
            if(i==j) continue;
            dp[i][j][0]=min(dp[i+1][j][0]+(pos[i+1]-pos[i])*help[i+1][j],
                            dp[i+1][j][1]+(pos[j]-pos[i])*help[i+1][j]
                           );
            dp[i][j][1]=min(dp[i][j-1][0]+(pos[j]-pos[i])*help[i][j-1],
                            dp[i][j-1][1]+(pos[j]-pos[j-1])*help[i][j-1]
                           );
            //cout<<"["<<i<<','<<j<<"]"<<dp[i][j][1]<<"="<<dp[i][j-1][1]<<"+"<<(pos[j]-pos[j-1])*help[i][j-1]<<endl;
        }

}
int main()
{
    init();
    //cout<<totPower<<endl;
    // 预处理
    preCalc();
    work();
    cout<<min(dp[1][N][0],dp[1][N][1]);
    return 0;
}
