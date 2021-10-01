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
int N,Q;
int s,i;
LL t;
// code
inline int BitCount4(LL n)
{
    unsigned int table[16] =
    {
        0, 1, 1, 2,
        1, 2, 2, 3,
        1, 2, 2, 3,
        2, 3, 3, 4
    } ;
    unsigned int count =0 ;
    while (n)
    {
        count += table[n &0xf] ;
        n >>=4 ;
    }
    return count ;
}
int main()
{
    scanf("%d%d",&N,&Q);
    for(i=1;i<=Q;++i)
    {
        scanf("%lld",&t);
        t-=1;
        s=BitCount4(t)%2;
        if(!s)    puts("X");
        else puts("Z");
    }
    return 0;
}