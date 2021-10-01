/**
垃圾陷阱
luogu P1156
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
#define INF 0x3f3f3f3f
int D,N;
int t[110],live[110],hei[110];
int dp[110][5000];//第二维3000会溢出
/**
状态转移方程定义
dp[i][j]    第i个垃圾扔下,生命还剩j小时时最大的高度
状态转移方程:
dp[i][j]=max(
            dp[i-1][j+(t[i]-t[i-1])]+hei[i],//不吃
            dp[i-1][j+(t[i]-t[i-1])-live[i]]//吃
             )
初始化:
dp[0][10]=0;
*/

void QuickSort(int *Array,int Left,int Right)
{
    int l=Left;
    int r=Right;
    int stand=Array[(Left+Right)/2];
    while(l<=r)
    {
        while(Array[l]<stand&&l<Right) l++;
        while(Array[r]>stand&&r>Left) r--;
        if(l<=r)
            {
                swap(Array[l++],Array[r--]);
                swap(live[l-1],live[r+1]);
                swap(hei[l-1],hei[r+1]);
            }
    }
    if(l<Right) QuickSort(Array,l,Right);
    if(r>Left)  QuickSort(Array,Left,r);
}


int main()
{
    memset(dp,0xc0,sizeof(dp));
    std::ios::sync_with_stdio(false);
    cin>>D>>N;
    for(int i=1; i<=N; i++)
        cin>>t[i]>>live[i]>>hei[i];
    if(t[1]>10)
    {
        cout<<10<<endl;
        exit(0);
    }
    QuickSort(t,1,N);
    dp[0][10]=0;
    for(int i=1; i<=N; i++)
    {
        for(int j=0; j<=3000; j++)
        {
            dp[i][j]=dp[i-1][j+(t[i]-t[i-1])]+hei[i];//不吃
            if(j-live[i]>=0)
                dp[i][j]=max(dp[i][j],dp[i-1][j+(t[i]-t[i-1])-live[i]]);
        }
    }
    int ansMinTime=INF,ansMaxLiveTime=-INF;
    for(int i=1; i<=N; i++)
        for(int j=0; j<=3000; j++)
            if(dp[i][j]>=D)
                ansMinTime=min(ansMinTime,t[i]);
            else if(dp[i][j]>=0)
                ansMaxLiveTime=max(j+t[i],ansMaxLiveTime);
    if(ansMinTime!=INF)
        cout<<ansMinTime<<endl;
    else
        cout<<ansMaxLiveTime<<endl;
    return 0;
}
