#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <utility>
#include <queue>
#include <stack>

using namespace std;
typedef long long LL;
const LL INF=0x3f3f3f3f;
LL P,N,a[1000100];
LL f[1000100],g[1000100];
// code
int main()
{
    scanf("%lld%lld",&N,&P);
    for(int i=1;i<=N;++i)
        scanf("%lld",a+i);
    f[1]=0;
    g[1]=1;
    for(int i=2;i<=N+1;++i)
    {
        f[i]=g[i-1]+1;
        g[i]=2*f[i]+1 -f[a[i]];
        f[i]=(f[i]%P+P)%P;
        g[i]=(g[i]%P+P)%P;
    }
    printf("%lld\n",f[N+1]%P);
    return 0;
}