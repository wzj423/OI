/*
HDU 2089
非递归
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
int N,M;
int bits[110],bitsLen;
int dp[110][2];
// code
void init()
{
    memset(bits,0,sizeof bits);
    memset(dp,-1,sizeof(dp));
    bitsLen=0;
}
int dfs(int pos,int pre,bool status,bool limit)
{
    if(pos==-1)
        return 1;//搜索到了最后,直接返回1
    if(limit==false&&dp[pos][status]!=-1)
        return dp[pos][status];
    int up=limit? bits[pos]: 9;
    int ret=0;
    for(int i=0;i<=up;++i)
    {
        if((pre==6&&i==2)||i==4)
            continue;
        ret+=dfs(pos-1,i,i==6,limit&&(i==bits[pos]));
    }
    if(!limit)
        dp[pos][status]=ret;
    return ret;
}
int solve(int num)
{
    bitsLen=0;
    while(num)
    {
        bits[bitsLen++]=num%10;
        num/=10;
    }
    return dfs(bitsLen-1,-1,0,true);
}
void work()
{
    printf("%d\n",solve(M)-solve(N-1));
}
int main()
{
    scanf("%d%d",&N,&M);
    while(N!=0&&M!=0)
    {
        init();
        work();
        scanf("%d%d",&N,&M);
    }
    return 0;
}