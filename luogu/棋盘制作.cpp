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
int N,M;
int mat[2010][2010];
int ex[2010][2010];
int ey[2010][2010];
int f[2010][2010];//正方形
int g[2010][2010][2];//矩形

int L[2010][2010];
int R[2010][2010];
int up[2010][2010];
// code
void init()
{
    memset(mat,0x3f,sizeof mat);
    scanf("%d%d",&N,&M);
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=M; ++j)
        {
            scanf("%d",&mat[i][j]);
            if((i+j)%2==0)
                mat[i][j]^=1;
        }
    //ext
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=M; ++j)
        {
            ex[i][j]=ey[i][j]=1;
            if(mat[i][j]==mat[i-1][j])
                ex[i][j]+=ex[i-1][j];
            if(mat[i][j]==mat[i][j-1])
                ey[i][j]+=ey[i][j-1];
        }
}
int square()
{
    int ans=0;
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=M; ++j)
        {
            f[i][j]=min(ex[i][j],min(ey[i][j],f[i-1][j-1]+1));
            ans=max(ans,f[i][j]);
        }
    return ans*ans;
}
int matrix()
{
    int ans=0;
    for(int i=1; i<=N; ++i)
    {
        for(int j=1; j<=M; ++j)
            if(mat[i][j]==mat[i][j-1])
                L[i][j]=L[i][j-1]+1;
            else
                L[i][j]=1;
        for(int j=M; j>=1; --j)
            if(mat[i][j]==mat[i][j+1])
                R[i][j]=R[i][j+1]+1;
            else
                R[i][j]=1;
    }
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=M; ++j)
        {
            if(mat[i][j]==mat[i-1][j])
            {
                up[i][j]=up[i-1][j]+1;
                L[i][j]=min(L[i][j],L[i-1][j]);
                R[i][j]=min(R[i][j],R[i-1][j]);
            }
            ans=max(ans,(up[i][j]+1)*(L[i][j]+R[i][j]-1));
        }
    return ans;
}
void work()
{
    printf("%d\n%d",square(),matrix());
}
int main()
{
    init();
    work();
    return 0;
}
