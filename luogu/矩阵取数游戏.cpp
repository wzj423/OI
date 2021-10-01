/**
矩阵取数游戏
LuoguP1005
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
typedef long long LL ;
int N,M;
int a[110][110];
LL dp[110][110];
const int lendit=53;
struct bnum
{
    int d[55];
    bnum() {memset(d,0,sizeof(d));}
    bnum(bnum& Other) {memcpy(d,Other.d,sizeof(d));}
    void mulInt(int num);
};
bnum operator + (bnum &a,bnum &b)
{
    bnum ret;
    ret.d[lendit]=max(a.d[lendit],b.d[lendit]);
    for(int i=1;i<=ret.d[lendit];++i)
    {
        ret.d[i]=a.d[i]+b.d[i];
        if(ret.d[i]>=10)
        {
            ++ret.d[i+1];
            ret.d[i]-=10;
            if(i+1>ret.d[lendit]);
                ++ret.d[lendit];
        }
    }
    return ret;
}
void bnum::mulInt(int num)
{
    int lenOther=log10(num);

    for(int i=1;i<=d[lendit];++i)
    {
        d[i]*=num;
        if(d[i]>=10)
        {
            d[i+1]+=d[i]/10;
            d[i]%=10;
        }
    }
    for(int i=d[lendit]+1;d[i]>=10;++i)
    {
        d[lendit]=i;
        d[i+1]+=d[i]/10;
        d[i]%=10;
    }
}
bnum powHelp[82];
// dp description
/*
1.思路 逐行dp 结果相加
2.dp数组描述:
    dp[i][j]表示某一行左边去到第i个,右边去到第j个的最大分数(i,j没有被去掉)
3.转移方程:
    int cur=(M-(j-i+1));
    dp[i][j]=MAX(
                 dp[i-1][j]+a[id][i-1]*2^cur, (i-1>=1)
                 dp[i][j+1]+a[id][j+1]*2^cur, (j+1<=M)
                 )
4.初始值:
    dp[1][M]=0;
*/
// code
inline LL MAX(LL a,LL b)
{
    return (a>b?a:b);
}
void init()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)
    {
        for(int j=1;j<=M;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
}
LL calcLine(int id)
{
    LL cur,ret=0;
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=M;++i)
    {
        for(int j=M;j>=i;--j)
        {
            if(i==1&&j==M) continue;
            cur=M-(j-i+1);
            if(i-1>=1)
                dp[i][j]=MAX(dp[i][j],dp[i-1][j]+a[id][i-1]*pow(2,cur));
            if(j+1<=M)
                dp[i][j]=MAX(dp[i][j],dp[i][j+1]+a[id][j+1]*pow(2,cur));
            //printf("(%lld,%lld) is %lld   And calc two value is %lld and %lld\n",i,j,dp[i][j],LL(dp[i-1][j]+a[id][i]*pow(2,cur)),LL(dp[i][j+1]+a[id][j]*pow(2,cur)));
        }
    }
    for(int i=1;i<=M;++i)
    {
        ret=MAX(ret,dp[i][i]+a[id][i]*pow(2,M));
    }
    return ret;
}
void work()
{
    LL ans=0;
    for(int i=1;i<=N;++i)
    {
        ans+=calcLine(i);
    }
    cout<<ans<<endl;
}
int main()
{
    init();
    work();
    return 0;
}
