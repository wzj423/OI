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
LL n,i,sum=1;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        sum*=i;
        while(sum%10LL==0LL) 
            sum/=10LL;
        sum%=100000000LL;
    }
    sum%=10;
    printf("%lld\n",sum);
    return 0;
}