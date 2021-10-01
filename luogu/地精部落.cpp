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
LL N,K;
LL f[2][4510];
LL sum[2][4510];
/**
f[n][i] 前n个里以i为开头,下降
i==n
    f[n][i]=f[n-1][1 to n-1]
i!=n && i!=1
    f[n][i]=f[n-1][n-i+1 to n-1]
i==1
    f[n][i]=0
f[2][2]=1 f[2][1]=0
*/
// code

int main()
{
    scanf("%lld%lld",&N,&K);
    f[2&1][2]=1;
    sum[2&1][0]=0;
    sum[2&1][1]=0;
    sum[2&1][2]=1;
    for(int i=3;i<=N;++i)
    {
        sum[i&1][0]=0;
        for(int j=1;j<=i;++j)
        {
            if(j==i)
                f[i&1][j]=sum[(i-1)&1][i-1];
            else if(j==1)
                f[i&1][j]=0;
            else
                f[i&1][j]=((sum[(i-1)&1][i-1]-sum[(i-1)&1][i-j])%K+K)%K;
            //printf("f[%d][%d]=%d\n",i,j,f[i&1][j]);
            sum[i&1][j]=sum[i&1][j-1]+f[i&1][j];

            f[i&1][j]%=K;
            sum[i&1][j]%=K;
        }        
    }
    printf("%lld\n",(sum[N&1][N]<<1)%K);
    return 0;
}