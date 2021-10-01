#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
int a[100010];
int f[100010][2];
int maxv=-INF;
int ans=-INF;
int N;
// code

int main()
{
    scanf("%d",&N);
    while(N)
    {   
        maxv=ans=-INF;
        for(int i=1;i<=N;++i)
            scanf("%d",a+i);
        memset(f,0xc0,sizeof f);
        for(int i=1;i<=N;++i)
        {

            f[i][0]=max(f[i-1][0]+a[i],a[i]);
            f[i][1]=max(f[i-1][1]+a[i],maxv+a[i]);
            maxv=max(maxv,f[i][0]);
            ans=max(ans,f[i][1]);
        }
        printf("%d\n",ans);
        scanf("%d",&N);
    }
    return 0;
}