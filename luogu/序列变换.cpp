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
int N;
int a[1001000];
int t[1001000],tcnt;

int f[1501000];//以下标i结尾的最大值
int g[1501000];//以值i结尾的最大值
#define Max(a,b) ((a)>(b)?(a):(b))
// code
void init()
{
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d",a+i);
        t[i]=a[i];
    }
    tcnt=N;
    sort(t+1,t+N+1);
    tcnt=unique(t+1,t+N+1)-t-1;
    for(int i=1; i<=N; ++i)
        a[i]=lower_bound(t+1,t+N+1,a[i])-t;
}
void work()
{
    int ans=0;
    for(int i=1;i<=N;++i)
    {
        f[i]=Max(g[a[i]]+1,g[a[i]-1]+1);
        g[a[i]]=Max(g[a[i]],f[i]);
        ans=Max(f[i],ans);
    }
    printf("%d\n",N-ans);
}
int main()
{
    init();
    work();
    return 0;
}