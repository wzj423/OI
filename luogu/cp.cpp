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
const int MAXN=2e3+10;
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
        printf("%c%d%d\n",c[0],x,y);
    }
    //printf("%d\n",ans);
    return 0;
}