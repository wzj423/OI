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
#include <utility>

#define ll long long
const ll mod=100003;
using namespace std;
/**
首先,我们可以计算出来一个局面所需要的最少次数
因为一个开关仅仅会被自己的倍数影响,所以从后往前地贪心一定是对的
但是这样预处理的时间复杂度是O(N\sqrt{N}),比较勉强
我们可以从一个点影响另一个点的关系出发,对于一个点,我们枚举它的倍数(他会被影响的点)
如果这个点不正确,那么在这个点打上一个标记.
这样的时间复杂度是O(NlogN),可以接受

然后就要考虑随机这部分的期望值的计算问题了
try1
我们考虑f[i]为期望到达最优方案长度为i步的期望随机行动步数
再考虑从f[i+1]转移到f[i]
那么现在还有i+1个点需要被点击
1.点击到了需要被点击的点->(i+1)/N*(f[i+1]+1)
2.点击到了不需要被点击的点(现在有i+2个点要被点击了)
    根据期望的线性性,我们有:chance=(N-i-1)/N
        需要的步数:f[i]-f[i+2]+1 (1是错误的那一步)
所以:
    f[i]=(i+1)/N*(f[i+1]+1)+(N-i-1)/N*(f[i]-f[i+2]+1)
        =1+inv[N]*( (i+1)*f[i+1] + (N-i-1)*(f[i]-f[i+2]) )


        f[i]=1+()
*/
ll N,K;
int a[100010];
int b[100010],tot;
ll f[100010],inv[100010],ans,fac=1;
int main() {

    scanf("%lld%lld",&N,&K);
    for(int i=1;i<=N;++i) scanf("%d",a+i),fac=(fac*i)%mod;
    for(int i=N;i>=1;--i) {
        int t=0;
        for(int j=i+i;j<=N;j+=i)
            t+=b[j];
        if(t%2!=a[i]) b[i]=1,++tot;
    }
    if(tot<=K) {
    	ans=fac*tot%mod;
        printf("%lld\n",ans);
        exit(0);
    }
    inv[1]=1;
    for(int i=2;i<=N;++i) inv[i]=(mod-(mod/i))*inv[mod%i]%mod;
    f[N]=1;
    for(int i=N-1;i>=1;--i) f[i] = (1+(N-i)*(f[i+1]+1)*inv[i])%mod;
    for(int i=K+1;i<=tot;++i) ans=(ans+f[i])%mod;
    ans=(ans+K)%mod;
    ans=(ans*fac)%mod;
    printf("%lld\n",ans);
    return 0;
}
