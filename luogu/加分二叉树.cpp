/**
加分二叉树
Luogu P1040
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
int a[40];
int dp[40][40];
int subRoot[40][40];
int N;
int ans;
// code
void init()
{
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d",&a[i]);
        dp[i][i]=a[i];
        subRoot[i][i]=i;
    }

}
int dfs(int st,int ed)
{
    int i;
    int maxValue=0,curValue=0,root=0;
    if(dp[st][ed]!=0)
    {
        return dp[st][ed];
    }

    if(st>ed)
    {
        return 1;
    }

    for(i=st; i<=ed; ++i)
    {
        curValue=a[i]+dfs(st,i-1)*dfs(i+1,ed);
        if(curValue>maxValue)
        {
            maxValue=curValue;
            root=i;
        }
    }
    dp[st][ed]=maxValue;
    subRoot[st][ed]=root;
    return maxValue;
}
void printSequence(int st,int ed)
{
    if(st>ed)
        return;
    cout<<subRoot[st][ed]<<" ";
    printSequence(st,subRoot[st][ed]-1);
    printSequence(subRoot[st][ed]+1,ed);

}
int  main()
{
    init();
    cout<<dfs(1,N)<<endl;
    printSequence(1,N);
    return 0;
}
