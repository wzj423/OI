/**
HDU 3555
dfs 记忆化搜索
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
typedef long long LL;
LL T,N;
LL dp[110][2];//dp[pos][digit(pos)==4]
LL bits[110],len;
// code
void init()
{
    scanf("%lld",&N);
    memset(dp,-1,sizeof(dp));
    memset(bits,0,sizeof bits);
    len=0;
    LL num=N;
    while(num)
    {
        bits[len++]=num%10;
        num/=10;
    }
}
LL dfs(LL pos,LL pre,LL status,LL limit)
{
    if(pos==-1)
        return 1;
    if(!limit&&dp[pos][status]!=-1)
        return dp[pos][status];
    LL up=limit? bits[pos]: 9;
    LL ret=0;
    for(LL i=0;i<=up;++i)
    {
        if(pre==4&&i==9)
            continue;
        ret+=dfs(pos-1,i,i==4,limit&&(i==bits[pos]));
    }
    if(!limit)
        dp[pos][status]=ret;
    return ret;
}
void work()
{
    printf("%lld\n",N+1-dfs(len-1,-1,false,true));
}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        init();
        work();
    }
    //system("pause");
    return 0;
}