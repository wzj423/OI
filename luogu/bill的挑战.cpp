#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
typedef long long LL;
const int mod=1000003;
#define lowbit(x) (x&(-x))
int T;
int N,K;

string a[60];
bool mat[20][60][30];//0-25 A-Z 26 ?
LL dp[55][1<<17];

int maxLen;

int num1[1<<16];
// code
void calc_num1()
{
    for(int i=1; i<(1<<16); ++i)
        num1[i]=num1[i>>1]+(i&1);
}
void init()
{
    maxLen=0;
    scanf("%d%d",&N,&K);
    for(int i=0; i<N; ++i)
    {
        cin>>a[i];
        for(int j=0; j<a[i].size(); ++j)
            for(int k=0; k<26; ++k)
                if(a[i][j]=='?'||k+'a'==a[i][j])
                    mat[i][j][k]=true;
    }
    maxLen=a[0].size();
}
int match(int now,int ch)//第now位,ch代表的字符
{
    int ret=0;
    for(int i=0;i<N;++i)
        if(a[i][now]=='?'||ch+'a'==a[i][now])
            ret|=(1<<i);
    return ret;
}
void work()
{
    memset(dp,0,sizeof dp);

    for(int k=0; k<26; ++k)
            dp[0][match(0,k)]++;
    for(int i=0; i<maxLen-1; ++i)
        for(int j=0; j<(1<<N); ++j)
        {
            if(!dp[i][j])   continue;
            for(int k=0; k<26; ++k)
            {
                int tar=match(i+1,k);
                dp[i+1][j&tar]+=dp[i][j];
                dp[i+1][j&tar]%=mod;
            }
        }
    LL ans=0;
    for(int j=0; j<(1<<N); ++j)
        if(num1[j]==K)
            ans+=dp[maxLen-1][j],ans%=mod;
    printf("%lld\n",ans);
}
int main()
{
    calc_num1();
    scanf("%d",&T);
    while(T--)
    {
        init();
        work();
    }
    return 0;
}