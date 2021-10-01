
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cctype>
#include <cmath>
#include <cstring>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int N;
int a[1101];
int dp[1100][1100];
// code
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
        scanf("%d",a+i);
    for(int i=1;i<=N;++i)
    {
        dp[i][0]=dp[i-1][0]+(a[i]==i);
        for(int j=1;j<=i;++j)
        {
            dp[i][j]=max(dp[i-1][j]+(a[i]==i-j),dp[i-1][j-1]);
        }
    }
    int ans=0;
    for(int i=1;i<=N;++i)
        ans=max(ans,dp[N][i]);
    printf("%d\n",ans);
    return 0;
}