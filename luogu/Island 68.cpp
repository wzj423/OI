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
const LL mod=19260817;
int N,M;
LL dis[200010];
LL num[200010];
LL sum[200010];
LL pre[200010];
LL back[200010];
// code
LL move1(int x,int L,int R)//move[L,R] to x,x<=L
{
    LL ret=0,t;
    ret=pre[R]-pre[L-1];
    ret -=((sum[R]-sum[L-1])*dis[x])%mod;
    return (ret%mod+mod)%mod;
}
LL move2(int x,int L,int R)//x>=R
{
    LL ret=0;
    ret=back[L]-back[R+1] -(sum[R]-sum[L-1])*(dis[N]-dis[x]);
    return (ret%mod+mod)%mod;
}
int main()
{
    //freopen("c:\\Users\\Mike-Wu\\Downloads\\oct_r2\\files\\1\\sample5.in","r+",stdin);
    //freopen("1.out","w+",stdout);
    scanf("%d%d",&N,&M);
    for(int i=2; i<=N; ++i)
    {
        LL x;
        scanf("%lld",&x);
        dis[i]=(x+dis[i-1])%mod;
    }
    for(int i=1; i<=N; ++i)
        scanf("%lld",num+i),num[i]%=mod;
    for(int i=1; i<=N; ++i)
        sum[i]=(sum[i-1]+num[i])%mod;
    for(int i=1; i<=N; ++i)
        pre[i]=(pre[i-1]+ num[i]*dis[i])%mod;//,printf("%d ",pre[i]);
    for(int i=N; i; --i)
        back[i]=(back[i+1]+ num[i]*(dis[N]-dis[i]))%mod;//,printf("%d ",back[i]);

    for(int i=1; i<=M; ++i)
    {
        int x,l,r;
        scanf("%d%d%d",&x,&l,&r);
        if(x<=l)
            printf("%lld\n",move1(x,l,r));
        else if(x>=r)
            printf("%lld\n",move2(x,l,r));
        else 
        {
            printf("%lld\n",(move2(x,l,x)+move1(x,x,r))%mod);
        }
    }
    return 0;
}