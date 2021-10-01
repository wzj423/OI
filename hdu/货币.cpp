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
typedef long long  LL;
const int MAXLIST=30000010;
LL dp[MAXLIST];
int T;
// code
LL dfs(LL num)
{
    if(num<3)
        return num;
    if(num<MAXLIST&&dp[num]!=0)
        return dp[num];
    if(num<MAXLIST)
        return dp[num]=max(num,dfs(num/2)+dfs(num/3)+dfs(num/4));
    else
        return max(num,dfs(num/2)+dfs(num/3)+dfs(num/4));
}
void work()
{
    LL N;
    scanf("%lld",&N);
    printf("%lld\n",dfs(N));
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        work();
    }
    // /system("pause");
    return 0;
}