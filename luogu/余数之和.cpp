#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include<string>

#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

typedef long long LL;
int main() 
{
    LL ans=0,p,q,n,k;
    scanf("%lld%lld",&n,&k);
    if(n>k)ans+=(n-k)*k,n=k;
    for(LL i=1; i<=n; i++) 
    {
        p=k/i;
        q=k%i;
        LL j=k/p;
        if(j>n)j=n;
        ans+=(q+q-(j-i)*p)*(j-i+1)/2;
        i=j;
    }
    printf("%lld\n",ans);
    return 0;
}