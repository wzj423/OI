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
/**
 * dp[1<<22]
 * 
 * dp[i] i状态下最大的可承重量
 * h[i]  i状态下总高度
 * g[i]  i状态下总重量
 * 
 * if(power[j]>=g[i])
 *      dp[j|i]=min(dp[j],power[i]-g[i])  
 * 
*/
// code
typedef long long LL ;
const LL INF=0x3f3f3f3f3f3f3f3fll;
LL ans=-1;
LL dp[1<<22],h[1<<22],g[1<<22];
LL N,HH;
LL height[30],weight[30],power[30];
void print_b(LL x)
{
    for(LL i=0;i<20;++i)
        printf("%d",(x&(1<<i))>=1);
    puts("");
}
int main()
{
    //print_b(3);
    scanf("%lld%lld",&N,&HH);
    for(LL i=0;i<N;++i)
        scanf("%lld%lld%lld",height+i,weight+i,power+i);
    for(LL i=0;i<(1<<N);++i)
        for(LL j=0;j<N;++j)
            if(i&(1<<j))
                h[i]+=height[j],g[i]+=weight[j];///预处理
    memset(dp,0x3f,sizeof dp);
    for(LL i=0;i<(1<<N);++i)
    {
        print_b(i),printf("\t%lld h=%lld g=%lld\n",dp[i],h[i],g[i]);
        for(LL j=0;j<N;++j)
        {
            if(( (1<<j) &i)==0)
            {
                if(power[j]>=g[i])
                {
                    LL t=min(dp[i],power[j]-g[i]);
                    if(dp[ (1<<j) |i]>=INF||dp[ (1<<j) |i]<t)
                        dp[ (1<<j) |i]=t;
                }
            }
        }
    }
    for(LL i=0;i<(1<<N);++i)
        if(dp[i]<INF&&h[i]>HH)
            ans=max(ans,dp[i]);
    if(ans==-1) puts("Mark is too tall");
    else        printf("%lld\n",ans);
    return 0;
}
