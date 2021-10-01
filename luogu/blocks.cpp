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

#define N 205

int T,n,Case;
int color[N],f[N][N][N];

int dp(int l,int r,int k)
{
    if (l>r) return 0;
    if (f[l][r][k]) return f[l][r][k];
    f[l][r][k]=dp(l,r-1,0)+(k+1)*(k+1);
    for (int i=r-1; i>=l; --i)
        if (color[i]==color[r])
            f[l][r][k]=max(f[l][r][k],dp(l,i,k+1)+dp(i+1,r-1,0));
    return f[l][r][k];
}
int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d",&n);
        for (int i=1; i<=n; ++i) scanf("%d",&color[i]);
        memset(f,0,sizeof(f));
        printf("Case %d: %d\n",++Case,dp(1,n,0));
    }
}