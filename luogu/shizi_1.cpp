/**
luogu P1052
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <cstring>
#include <cmath>
#include <cctype>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

#define INF 0x3f3f3f3f
#define DBG //while(0)
int L,S,T,M,ans=INF;
int dp[1000010];

int sto[110];
void tight()
{
    for(int i=0;i<=M-1;i++)
    {
        int s=sto[i];
        int t=sto[i+1];
        if((t-s-2*T)/T>=1)
        {
            int del=(t-s-2*T)/T*T;
            L-=del;
            for(int j=i+1;j<=M;j++)
                sto[j]-=del;
        }
    }
    int stoMax=sto[M];
    int del=(L-stoMax-2*T)/T*T;
    L-=del;
}
int main()
{
    std::ios::sync_with_stdio(false);
    memset(dp,0x3f,sizeof(dp));
    cin>>L>>S>>T>>M;
    for(int i=1; i<=M; i++)
        cin>>sto[i];
    sort(sto+1,sto+M+1);
    dp[0]=0;
    tight();
    for(int i=1; i<=M; i++)
        dp[sto[i]]+=1;
    for(int i=1; i<=L; i++)
    {
        bool b=(dp[i]==INF+1);
        for(int j=i-S; j>=0&&j>=i-T; j--)
            dp[i]=min(dp[i],dp[j]);
        dp[i]+=b;
    }
    for(int i=L; i>=L-S; i--)
        ans=min(ans,dp[i]);
    cout<<ans<<endl;
    return 0;
}
