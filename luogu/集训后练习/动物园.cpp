/**
动物园
50
TLE 5/10
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
int NextPre[1000010];
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
    NextPre[1]=0;
    int i,j;
    for(i=2; i<=len; ++i)
    {
        for(j=Next[i-1]; j>0&&S[j+1]!=S[i]; j=Next[j]);
        Next[i]=j+(S[j+1]==S[i]);
        j=Next[i];
        while(2*j>i)
            j=Next[j];
        if(j>0)
        {
            ++Num[i];
            Num[i]+=NextPre[Next[j]];
            NextPre[j]=NextPre[Next[j]]+1;
        }
        else
        {
            NextPre[j]=0;
        }
        /*while(j>0)
        {
            ++Num[i];
            j=Next[j];
        }*/
        //printf("id:%d Num:%d Next:%d NextPre:%d\n",i,Num[i],Next[i],NextPre[i]);
        ans=ans*(Num[i]+1)%mod;
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
