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
int N,M,R;
struct mk{int b,e,vv;}k[1010];
int dp[1010];
int ans=0;
// code
bool cmp(mk a,mk b)
{
    return a.b<b.b;
}
int main()
{
    scanf("%d%d%d",&N,&M,&R);
    for(int i=1; i<=M; ++i)
    {
        scanf("%d%d%d",&k[i].b,&k[i].e,&k[i].vv);
        k[i].e+=R;
    }
    sort(k+1,k+M+1,cmp);
    for(int i=1; i<=M; ++i)
    {
        for (int j = 0; j < i; ++j)
            if(k[j].e<=k[i].b)
                dp[i]=max(dp[i],dp[j]+k[i].vv);
        ans=max(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}