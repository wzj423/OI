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
const int MAXN=2e3+10,INF=0x3f3f3f3f;
typedef long long LL;
int N,M;
int price[MAXN][2];
LL f[MAXN][MAXN];
char ss[MAXN];
// code


int main()
{
    memset(price,0x3f,sizeof price);
    scanf("%d%d",&N,&M);
    scanf("%s",ss+1);
    for(int i=1;i<=N;++i)
    {
        char c[2];int x,y;
        scanf("%1s%d%d",c,&x,&y);
        //printf("%c%d%d\n",c[0],x,y);
        price[ c[0] ][0]=x,price[ c[0] ][1]=y;
    }
    for(int i=1;i<=M;++i)
    {
        for(int j=i-1;j;--j)
        {
            f[j][i]=INF;
            if(ss[i]==ss[j])    f[j][i]=f[j+1][i-1];
            f[j][i]=min(f[j][i], f[j][i-1]+min(price[ ss[i] ][0] , price[ ss[i] ][1] )  );
            f[j][i]=min(f[j][i], f[j+1][i]+min(price[ ss[j] ][0] , price[ ss[j] ][1] )  );
        }
    }
    printf("%lld\n",f[1][M]);
    return 0;
}