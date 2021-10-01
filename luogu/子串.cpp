#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include<string>

#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;
int N,M,K;
char A[1010],B[210];
const int mod=1e9+7;
int f[10][210][210];
int g[10][210][210];
/*
f[i][j][k] => A到i(必须),B到j(必须),有k段
g[i][j][k] => A到i(非必须),B到j(必须),有k段
if(A[i]==B[j])
    f[i][j][k]=g[i-1][j-1][k-1]+f[i-1][j-1][k];
else
    f[i][j][k]=0;
g[i][j][k]=g[i-1][j][k]+f[i][j][k];
*/
// code
void init()
{
    scanf("%d%d%d",&N,&M,&K);
    scanf("%s",A+1);
    scanf("%s",B+1);
}
void work()
{
    g[0][0][0]=1;
    for(int i=1; i<=N; ++i)
    {
        g[i&1][0][0]=1;// Hint!!!!!!!!!!!!!!!!!!!!!
        for(int j=1; j<=M; ++j)
            for(int k=1; k<=K; ++k)
            {
                if(A[i]==B[j])
                    f[i&1][j][k]=(g[(i-1)&1][j-1][k-1]+f[(i-1)&1][j-1][k])%mod;
                else
                    f[i&1][j][k]=0;
                g[i&1][j][k]=(g[(i-1)&1][j][k]+f[i&1][j][k])%mod;
            }
    }
    printf("%d\n",g[N&1][M][K]);
}
int main()
{
    init();
    work();
    return 0;
}