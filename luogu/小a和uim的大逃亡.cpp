/**
大逃亡
LuoguP1373
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
int N,M,K;
int ans;
int a[1000][1000];
int dp[805][805][18][2];
const int mod=1000000007;
/*
dp[i][j][k][b] 表示以i,j坐标为结尾,差值为k,下一步是编号为b的人走的状态数
                b=0 小a
                b=1 uim
                差值 a-b
//转移方程
dp[i][j][k][1]+=(dp[i-1][j][k-a[i][j]][0]+dp[i][j-1][k-a[i][j]][0]);
dp[i][j][k][0]+=(dp[i-1][j][k+a[i][j]][1]+dp[i][j-1][k-a[i][j]][1]);
//初始状态
dp[i][j][a[i][j]][1]=1;
//答案
统计所有 dp[i][j][0][0]之和
*/
// code
void init()
{
    scanf("%d%d%d",&N,&M,&K);
    ++K;
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=M; ++j)
        {
            scanf("%d",&a[i][j]);
            dp[i][j][a[i][j]][1]=1;
        }
}
void work()
{
    for(int i=1; i<=N; ++i)
    {
        for(int j=1; j<=M; ++j)
        {
            for(int k=0; k<=K; ++k)
            {
                dp[i][j][k][1]+=(dp[i-1][j][(k-a[i][j]+100*K)%K][0]+dp[i][j-1][(k-a[i][j]+100*K)%K][0]);
                dp[i][j][k][0]+=(dp[i-1][j][(k+a[i][j]+100*K)%K][1]+dp[i][j-1][(k+a[i][j]+100*K)%K][1]);
                dp[i][j][k][1]%=mod;
                dp[i][j][k][0]%=mod;
            }
        }
    }
    for(int i=1; i<=N; ++i)
    {
        for(int j=1; j<=M; ++j)
        {
            ans+=dp[i][j][0][0];
            ans%=mod;
        }
    }
    cout<<ans<<endl;
}
int main()
{
    init();
    work();
    return 0;
}
