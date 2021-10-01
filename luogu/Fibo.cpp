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
const LL INF=0x3f3f3f3f;
LL a[1010];
int M;

// code
void deal()
{
    LL x,y;
    scanf("%lld%lld",&x,&y);
    int px=lower_bound(a+1,a+68+1,x)-a,py=lower_bound(a+1,a+68+1,y)-a;
    while(x!=y)
    {
        if(px<py)
            swap(px,py),swap(x,y);
        while(a[px]>=x)  --px;
        x-=a[px];
        while(a[px]>=x)  --px;
        //printf("%d(%d) %d(%d)\n",x,px,y,py);
    }
    printf("%lld\n",x);
}
int main()
{
    a[0]=a[1]=1;
    for(int i=2; i<=70; ++i)
        a[i]=a[i-1]+a[i-2];
    a[0]=0;
    scanf("%d",&M);
    while(M--)
    {
        deal();
    }
    return 0;
}