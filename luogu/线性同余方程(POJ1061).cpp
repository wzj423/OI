/**
蚯蚓
Luogu P2827
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
LL S1,S2,A,B,L;
// code

void init()
{
    scanf("%lld%lld%lld%lld%lld",&S1,&S2,&A,&B,&L);
}
LL exgcd(LL a,LL b,LL &x,LL &y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    LL ret=exgcd(b,a%b,x,y);
    LL t=y;
    y=x-(a/b)*y;
    x=t;
    return ret;
}

void work()
{
    LL x,y;
    LL a=A-B,b=L,c=S2-S1;
    if(a<0)
    {
        a=-a;
        c=-c;
    }
    //printf("%d %d %d\n",a,b,c);
    LL d=exgcd(a,b,x,y);
    if(c%d)
    {
        printf("Impossible\n");
        exit(0);
    }
    else
    {
        LL k=c/d;
        //cout<<k<<endl;
        x*=k;
        x=(x%(L/d)+(L/d))%(L/d);
        printf("%lld\n",x);
        exit(0);
    }
    cout<<x<<endl;
}
int main()
{
    init();
    work();
    return 0;
}






