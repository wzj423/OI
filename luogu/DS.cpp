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
LL delta[100010],a[100010],pre[100010];
LL N,M,P,maxv,minv,F;
// code
void add()
{
    LL l,r,x;
    scanf("%lld%lld%lld",&l,&r,&x);
    delta[r+1]-=x;
    delta[l]+=x;
}
void query()
{
    LL l,r,ret=0,t;
    scanf("%lld%lld",&l,&r);
    a[0]=0;
    for(int i=1;i<=N;++i)
        a[i]=(a[i-1]+delta[i]); 
    for(int i=l;i<=r;++i)
    {
        t=(a[i]%P*i)%P;    
        if(minv<=t&&t<=maxv)
            ++ret;
    }
    printf("%lld\n",ret);
}
void build_pre()
{
    a[0]=0;
    for(int i=1;i<=N;++i)
        a[i]=(a[i-1]+delta[i]);   
    for(int i=1;i<=N;++i)
    {
        a[i]=(a[i]%P*i)%P;
        pre[i]=pre[i-1]+(a[i]>=minv&&a[i]<=maxv);
    }
    pre[0]=0;
}
int main()
{
    scanf("%lld%lld%lld%lld%lld",&N,&M,&P,&minv,&maxv);
    //printf("N=%lld M=%lld %lld%lld%lld\n",N,M,P,minv,maxv);
    while(M--)
    {
        char ch;
        scanf("%1s",&ch);
        if(ch=='Q')  query();
        else if(ch=='A') add();
    }
    scanf("%lld",&F);
    build_pre();
    while(F--)
    {
        LL l,r;
        scanf("%lld%lld",&l,&r);
        printf("%lld\n",pre[r]-pre[l-1]);
    }
    return 0;
}