/**
动物园
AC
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
const int mod=1e9+7;
char S[1000010];
int len;
int Next[1000010];
int Cnt[1000010];
int Num[1000010];
int N;
LL ans;
// code
void init()
{
    memset(S,0,sizeof S);
    memset(Next,0,sizeof Next);
    memset(Num,0,sizeof Num);
    scanf("%s",S+1);
    len=strlen(S+1);
    ans=1;
}
void work()
{
    Next[1]=0;
    Cnt[1]=1;
    int i,j;
    for(i=2; i<=len; ++i)
    {
        for(j=Next[i-1]; j>0&&S[j+1]!=S[i]; j=Next[j]);
        int P=j+(S[j+1]==S[i]);
        Next[i]=P;
        Cnt[i]=Cnt[P]+1;
    }
    for(j=0,i=2;i<=len;++i)
    {
        for(;j&&S[j+1]!=S[i];j=Next[j]);
        j+=S[j+1]==S[i];
        while(j*2>i) j=Next[j];
        ans*=Cnt[j]+1;
        ans%=mod;
    }
    printf("%lld\n",ans);
    ans=1;
}
int main()
{
    scanf("%d",&N);
    while(N--)
    {
        init();
        work();
    }
    return 0;
}

