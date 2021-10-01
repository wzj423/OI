/**
组合数问题
Luogu P2822
*/
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

int T,K;
int N,M;
//杨辉三角
int help[3000][3000];
int ansNum[3000][3000];//前缀和储存结果
// code
void preCalc(int LineNum=2000)
{
    help[1][1]=1;
    for(int i=2; i<=LineNum; ++i)
    {
        for(int j=1; j<=i; ++j)
        {
            help[i][j]=(help[i-1][j-1]%K+help[i-1][j]%K)%K;
            if(help[i][j]==0)
                ansNum[i-1][j-1]=ansNum[i-1][j-2]+1;
            else
                ansNum[i-1][j-1]=ansNum[i-1][j-2];
            //cout<<help[i][j]<<" ";
        }
        //cout<<endl;
    }
    if(0)for(int i=1; i<=15; ++i)
    {
        for(int j=1; j<=i; ++j)
        {
            printf("%d ",ansNum[i][j]);
        }
        printf("\n");
    }
}
void init()
{
    scanf("%d%d",&T,&K);
    preCalc();
}

void work()
{

    for(int i=1; i<=T; ++i)
    {
        int ans=0;
        scanf("%d%d",&N,&M);
        for(int j=1; j<=N; ++j)
        {
            ans+=ansNum[j][min(j,M)];
        }
        printf("%d\n",ans);
    }
}
int main()
{
    init();
    work();
    return 0;
}



