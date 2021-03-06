#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#define RG register
#define il inline
#define iter iterator
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
using namespace std;
const int N=55;
int n,a[N],f[N][N][N][N];
void work()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=a[i];j++)
            for(int k=a[i];k<=50;k++)
                f[i][i][j][k]=1;
    }
    for(int k=2;k<=n;k++){
        for(int l=1;l<=n;l++){
            int r=l+k-1;if(r>n)break;
            for(int i=1;i<=50;i++){
                for(int j=i;j<=50;j++){
                f[l][r][i][j]=Max(f[l][r][i][j],
                Max(f[l+1][r][i][j]+(a[l]==i),
                                f[l][r-1][i][j]+(a[r]==j)));
                f[l][r][i][j]=Max(f[l][r][i][j],
                                f[l+1][r-1][i][j]+
                                (a[r]==i)+(a[l]==j));
                f[l][r][i][j+1]=
                                Max(f[l][r][i][j+1],f[l][r][i][j]);
                f[l][r][i-1][j]=
                                Max(f[l][r][i-1][j],f[l][r][i][j]);
                }
            }
            for(int j=1;j<=50;j++)
                for(int i=j;i>=1;i--)
                f[l][r][i-1][j]=Max(f[l][r][i-1][j],f[l][r][i][j]);
        }
    }
    printf("%d\n",f[1][n][1][50]);
}

int main()
{
    work();
    return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
