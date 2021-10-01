/**
/**
P1736
90
WA at 4
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <cstring>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>
#define DBG while(0)
using namespace std;
short a[2510][2510];
int pre[2510][2510];
int dp[2510][2510][2];
int N,M;
//FILE* dbg=fopen("1.txt","w+");
int main()
{
    std::ios::sync_with_stdio(false);
    //cout<<sizeof(int)<<" "<<sizeof(short)<<" "<<sizeof(long)<<" "<<sizeof(long long)<<" "<<sizeof(bool)<<" "<<sizeof(char)<<endl;
    cin>>N>>M;
    for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=M; j++)
        {
            cin>>a[i][j];
            pre[i][j]=pre[i][j-1]+a[i][j];
        }
    }
    for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=M; j++)
        {
            pre[i][j]+=pre[i-1][j];
        }
    }

    for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=M; j++)
        {
            if(a[i][j])
            {
                int length=dp[i-1][j-1][0]+1;
                int fishNum=pre[i][j]-pre[i-length][j]-pre[i][j-length]+pre[i-length][j-length];
                //fprintf(dbg,"%d %d (%d,%d)\n",length,fishNum,i,j);
                if(fishNum==length)
                    dp[i][j][0]=dp[i-1][j-1][0]+1;
                else
                    dp[i][j][0]=1;

                ///
                length=dp[i-1][j+1][1]+1;
                fishNum=pre[i][j+length-1]-pre[i-length][j+length-1]-pre[i][j-1]+pre[i-length][j-1];
                //fprintf(dbg,"%d %d (%d,%d)\n",length,fishNum,i,j);
                if(fishNum==length)
                    dp[i][j][1]=dp[i-1][j+1][1]+1;
                else
                    dp[i][j][1]=1;
            }
        }
    }
    DBG for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=M; j++)
        {
            if(a[i][j])
            {
                int length=dp[i-1][j+1][1]+1;
                int fishNum=pre[i][j+length-1]-pre[i-length][j+length-1]-pre[i][j-1]+pre[i-length][j-1];
                //fprintf(dbg,"%d %d (%d,%d)\n",length,fishNum,i,j);
                if(fishNum==length)
                    dp[i][j][1]=dp[i-1][j+1][1]+1;
                else
                    dp[i][j][1]=1;
            }
        }
    }
    DBG for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=M; j++)
        {
            cout<<dp[i][j][1]<<" ";
        }
        cout<<endl;
    }

    int ans=0;
    for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=M; j++)
        {
            ans=max(ans,dp[i][j][0]);
            ans=max(ans,dp[i][j][1]);
        }
    }
    cout<<ans<<endl;
    return 0;
}
