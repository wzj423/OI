/**
Hankson
Luogu P1072
90
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
int a0,a1,b0,b1;
int N;
// code

void init()
{
    scanf("%d%d%d%d", &a0,&a1,&b0,&b1);
}
int gcd(int a,int b)
{
    if(b>a) swap(b,a);
    if(b==0)
        return a;
    return gcd(b,a%b);
}
void work()
{
    int ans=0,x;
    for(int i=1;i*i<=b1;++i)
    {
        x=i;
        if(b1%x==0&&x%a1==0)
        {
            if(gcd(x/a1,a0/a1)==1&&gcd(b1/b0,b1/x)==1)
                ++ans;
        }
        x=b1/i;
        if(x!=i&&b1%x==0&&x%a1==0)
        {
            if(gcd(x/a1,a0/a1)==1&&gcd(b1/b0,b1/x)==1)
                ++ans;
        }
    }
    printf("%d\n",ans);
}
int main()
{
    scanf("%d",&N);
    while(N--)
    {
        init();
        work();
    }
    return 0;
}


