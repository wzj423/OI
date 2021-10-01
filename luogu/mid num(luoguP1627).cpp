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
const int MAXN=1e5+10;
typedef long long LL;
int a[MAXN],N,B,pos;
int before[MAXN*4],after[MAXN*4];
LL ans;
// code

int main()
{
    scanf("%d%d",&N,&B);
    for(int i=1;i<=N;++i)
    {
        int x;
        scanf("%d",&x);
        if(x>B) a[i]=1;
        else if(x==B)   a[i]=0,pos=i;
        else    a[i]=-1;
    }
    before[MAXN]=after[MAXN]=1;
    int t=0;
    for(int i=pos-1;i>0;--i)
    {
        t+=a[i];
        ++before[t+MAXN];
    }
    t=0;
    for(int i=pos+1;i<=N;++i)
    {
        t+=a[i];
        ++after[t+MAXN];
    }
    ans=before[MAXN]*after[MAXN];
    for(int i=1;i<=N;++i)
    {
        ans+=before[MAXN+i]*after[MAXN-i]+before[MAXN-i]*after[MAXN+i];
    }
    printf("%lld\n",ans);
    return 0;
}