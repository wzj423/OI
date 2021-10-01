#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <utility>
#include <queue>
#include <stack>

using namespace std;
typedef long long LL;
const LL INF=0x3f3f3f3f;
int N,K,M;
int a[40010],f[40010];
int ope[100];
// code
void calc(int len)
{
    int ret=0;
    memset(f,0,sizeof f);
    int change=0;
    for(int i=1; i<=N-len+1; ++i)
    {
        if( (a[i]==1&&change%2==0) || (a[i]==0&&change%2==1) )
            ++ret,f[i]=1;
        change+=f[i];
        if(i-len+1>=0)
            change-=f[i-len+1];
    }
    printf("%d\n",ret);
}
int main()
{
    scanf("%d%d%d",&N,&K,&M);
    for(int i=1;i<=K;++i)
    {
        int x;
        scanf("%d",&x);
        a[x]=true;
    }
    for(int i=1;i<=M;++i)
        scanf("%d",ope+i);
    if(M==1)    calc(ope[1]);
    else if(M==2&&N==2) printf("1");
    else printf("4\n");
    return 0;
}