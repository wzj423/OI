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
char S[1000100];
char Sf[1100];
int N,M;
int Next[1000100];
int F[1000100];
// code
void init()
{
    scanf("%s",S+1);
    scanf("%s",Sf+1);
    N=strlen(S+1);
    M=strlen(Sf+1);
}
void work()
{
    /// calc Next;
    Next[1]=0;
    int i,j;
    for(i=2;i<=N;++i)
    {
        for(j=Next[i-1];j&&Sf[j+1]!=Sf[i];j=Next[j]);
        Next[i]=j+(Sf[j+1]==Sf[i]);
    }
    for(i=1;i<=N;++i)
    {
        for(j=F[i-1];j&&Sf[j+1]!=S[i];j=Next[j]);
        F[i]=j+(Sf[j+1]==S[i]);
        if(F[i]==M)
            printf("%d\n",i-M+1);
    }
    for(int i=1;i<=M;++i)
        printf("%d ",Next[i]);
}
int main()
{
    init();
    work();
    return 0;
}
