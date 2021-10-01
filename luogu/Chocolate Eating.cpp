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
const LL INF=124976992640l;
LL N,D;
LL a[50010];
LL d[50010];
// code
bool judge(LL vv)
{
    LL ret=0,hapi=0;
    int id=1;
    for(int i=1;i<=D;++i)
    {
        hapi>>=1;
        while(id<=N&&hapi<vv)
            hapi+=a[id],d[id]=i,++id;
        if(hapi<vv)
            return false;
    }
    for(;id<=N;++id)
        d[id]=D;
    return true;
}
int main()
{
    scanf("%lld%lld",&N,&D);
    for(LL i=1; i<=N; ++i)   scanf("%lld",a+i);
    LL L=0,R=INF;
    while(L<=R)
    {
        LL mid=(L+R)/2;
        if(judge(mid))
            L=mid+1;
        else
            R=mid-1;
    }
    printf("%lld\n",L-1);
    judge(L-1);
    for(LL i=1; i<=N; ++i)
        printf("%lld\n",d[i]);
    return 0;
}