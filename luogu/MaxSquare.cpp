#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#define _min(a,b,c)  min(a,min(b,c))
using namespace std;
int sq[110][110];
int dp[110][110];
int N,M,ans;
/**
dp[i][j] 以sq[i][j]为右下角的最大正方形的边长
转移方程
sq[i][j]==0
    dp[i][j]=0
sq[i][j]==1
    dp[i][j]=min{dp[i-1][j],
                dp[i][j-1],
                dp[i-1][j-1]}+1
*/
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>N>>M;
    for(int i=1; i<=N; i++)
        for(int j=1; j<=N; j++)
        {
            cin>>sq[i][j];
            if(sq[i][j])
            {
                dp[i][j]=_min(dp[i-1][j],dp[i-1][j-1],dp[i][j-1])+1;
                ans=max(ans,dp[i][j]);
            }
        }
    cout<<ans<<endl;
    return 0;
}
