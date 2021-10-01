#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
int N,C;
int mat[1040][1040];//手动滑稽
int dp[1040];//到第i年末刚好用完电脑的最少花费
// code

int main()
{
    while(scanf("%d%d",&C,&N)!=EOF)
    {
        memset(dp,0x3f,sizeof dp);
        memset(mat,0x3f,sizeof mat);
        for(int i=1; i<=N; ++i)
            for(int j=i; j<=N; ++j)
                scanf("%d",&mat[i][j]);
        dp[0]=0;
        for(int i=1; i<=N; ++i)
            for(int j=0; j<i; ++j)
                dp[i]=min(dp[i],dp[j]+C+mat[j+1][i]);
        printf("%d\n",dp[N]);
    }
    return 0;
}