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
int N,st,maxn,a[1001];
bool dp[1001][1001];
int main()
{
    scanf("%d%d%d",&N,&st,&maxn);
    memset(dp,0,sizeof(dp));
    for(int i=1; i<=N; ++i)
        scanf("%d",&a[i]);
    dp[0][st]=1;
    for(int i=1; i<=N; ++i)
        for(int j=0; j<=maxn; ++j)
        {
            if(dp[i-1][j]&&j+a[i]<=maxn) dp[i][j+a[i]]=true;
            if(dp[i-1][j]&&j-a[i]>=0) dp[i][j-a[i]]=true;
        }
    for(int i=maxn; i>=0; --i)
        if(dp[N][i])
        {
            printf("%d\n",i);
            exit(0);
        }
    puts("-1\n");
}
