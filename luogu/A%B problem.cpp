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

int pre[11000000];

bool isPrime[11000000];
int primeSize;
int prime[1100000];
// code
void getList(int listSize)
{
    memset(isPrime,true,sizeof(isPrime));
    isPrime[1]=false;
    for(int i=2;i<=listSize;++i)
    {
        if(isPrime[i])
            prime[++primeSize]=i;
        for(int j=1;j<=primeSize&&i*prime[j]<=listSize;++j)
        {
            isPrime[i*prime[j]]=false;
            if(i%prime[j]==0)   break;
        }
    }
}
int main()
{
    scanf("%d%d",&N,&M);
    getList(M+5);
    for(int i=1;i<=M+5;++i)
    {
        pre[i]=pre[i-1]+isPrime[i];
    }
    int L,R;
    for(int i=1;i<=N;++i)
    {
        scanf("%d%d",&L,&R);
        if(L>M||L<1||R>M||R<1)
        {
            puts("Crossing the line");
        }
        else
        {
            printf("%d\n",pre[R]-pre[L-1]);
        }
    }
    return 0;
}
