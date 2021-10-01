/**
聪明的质检员
Luogu P1314
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
const int MAXN=200010;
LL N,M,S;
LL ww[MAXN],vv[MAXN];
LL sec[MAXN][2];
//预处理前缀和
LL preNum[MAXN];//前i个中满足条件的数量（包括第i个）
LL preVV[MAXN];//前i个中满足条件的权值之和（包括第i个）
//二分用变量
LL L=0;
LL R=0;
LL mid;
LL ans=LL(INFINITY);
// code
LL ABS(LL a,LL b)
{
    return (a>b?a-b:b-a);
}
void init()
{
    scanf("%lld%lld%lld",&N,&M,&S);
    for(int i=1;i<=N;++i)
    {
        scanf("%lld%lld",&ww[i],&vv[i]);
        R=max(ww[i],R);
    }
    for(int i=1;i<=M;++i)
    {
        scanf("%lld%lld",&sec[i][0],&sec[i][1]);
    }
}
LL preCalc(int W)
{
    LL ret=0;
    memset(preNum,0,sizeof(preNum));
    memset(preVV,0,sizeof(preVV));
    for(int i=1;i<=N;++i)
    {
        preNum[i]=preNum[i-1]+(ww[i]>=W);
        preVV[i]=preVV[i-1]+(ww[i]>=W?vv[i]:0);
    }
    for(int i=1;i<=M;++i)
    {
        int l=sec[i][0],r=sec[i][1];
        ret+=(preNum[r]-preNum[l-1])*(preVV[r]-preVV[l-1]);
    }
    return ret;
}
void work()
{
    LL t;
    while(L<=R)
    {
        mid=(L+R)/2;
        t=preCalc(mid);
        if(t>S)//t取大了，W太小了
        {
            L=mid+1;
            if(t-S<ans)
                ans=t-S;
        }
        else if(t<S)
        {
            R=mid-1;
            if(S-t<ans)
                ans=S-t;
        }
        else
        {
            ans=0;
            break;
        }
    }
}
int main()
{
    init();
    work();
    cout<<ans<<endl;
    //cout<<preCalc(4)-S<<endl;
    return 0;
}

