/**
P1508
*/

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

using namespace std;
#define MAX(a,b,c) max(a,max(b,c))
int a[210][210];
int dp[210][210];
int M, N;

int main()
{
    std::ios::sync_with_stdio(false);
    cin >> M >> N;
    for(int i = 1; i <= M; i++)
        for(int j = 1; j <= N; j++)
        {
            cin >> a[i][j];
            if(j == 1)
                dp[i][j] = a[i][j] + max(dp[i - 1][j], dp[i - 1][j + 1]);
            else if(j == N)
                dp[i][j] = a[i][j] + max(dp[i - 1][j], dp[i - 1][j -1]);
            else
                dp[i][j] = a[i][j] + MAX(dp[i - 1][j], dp[i - 1][j - 1], dp[i - 1][j + 1]);
        }
    cout<<MAX(dp[M][N/2],dp[M][N/2+1],dp[M][N/2+2])<<endl;
    return 0;
}
