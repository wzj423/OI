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
const LL INF=0x3f3f3f3f;

int N,K;
int a[1000100];
int table[1000100];

int ff[1050][1050],gg[1050][1050],ss[1050][1050];
int dp[1050],from[1050];
vector<int> ans;
// code
void solve1()
{
    memset(dp,0x3f,sizeof dp);
    dp[0]=0;
    for(int i=1;i<=N;++i)
    {
        for(int j=0;j<i;++j)
            if(gg[j+1][i]==0&&dp[j]+1<dp[i])
                dp[i]=dp[j]+1,from[i]=j; 
        //printf("dp[%d]=%d,from[%d]=%d\n",i,dp[i],i,from[i]);       
    }

    int t=from[N];
    //ans.push_back(t);
    while(t!=0)
    {
        ans.push_back(t);
        t=from[t];
    }
    printf("%d\n",ans.size()+1);
    for(int i=ans.size()-1;i>=0;--i)
        printf("%d ",ans[i]);
    puts("");
}
int q1[1050],q2[1050],p1,p2;
bool check(int L,int R)
{
    p1=p2=0;
    q1[0]=q2[0]=0;
    for(int i=L;i<=R;++i)
    {

        bool b=true;
        for(int j=1;j<=p1;++j)
             if(table[a[i]+q1[j]])
             {
                 b=false;
                 break;
              }
        if(b)
        {
            q1[++p1]=a[i];   
            continue;             
        }
        b=true;
        for(int j=1;j<=p2;++j)
             if(table[a[i]+q2[j]])
             {
                 b=false;
                 break;
              }
        if(b)
        {
            q2[++p2]=a[i];   
            continue;             
        }
        return false;
    }
    return true;
}
void solve2()
{
    memset(dp,0x3f,sizeof dp);
    dp[0]=0;
    for(int i=1;i<=N;++i)
    {
        for(int j=0;j<i;++j)
            if(dp[j]+1<dp[i]&&check(j+1,i))
                dp[i]=dp[j]+1,from[i]=j; 
        //printf("dp[%d]=%d,from[%d]=%d\n",i,dp[i],i,from[i]);       
    }

    int t=from[N];
    //ans.push_back(t);
    while(t!=0)
    {
        ans.push_back(t);
        t=from[t];
    }
    printf("%d\n",ans.size()+1);
    for(int i=ans.size()-1;i>=0;--i)
        printf("%d ",ans[i]);
    puts("");
}
int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;++i)
        scanf("%d",a+i);
    for(int i=1;i*i<=1000000;++i)
        table[i*i]=true;
    for(int j=2;j<=N;++j)
        for(int i=j-1;i>=1;--i)
            ff[i][j]=ff[i+1][j]+table[a[i]+a[j]];//,printf("%d [%d,%d]\n",ff[i][j],i,j);
    for(int j=1;j<=N;++j)
        for(int i=j+1;i<=N;++i)
            ss[i][j]=ss[i-1][j]+table[a[i]+a[j]];
    for(int i=1;i<=N;++i)
        for(int j=i+1;j<=N;++j)
            gg[i][j]=gg[i][j-1]+ff[i][j];//,printf("g[%d,%d]=%d\n",i,j,gg[i][j]);
    if(K==1) solve1();
    else solve2();
    return 0;   
}