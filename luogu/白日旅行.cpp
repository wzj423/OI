
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cctype>
#include <cmath>
#include <cstring>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int N,P,Q;
int f[2000010],g[2000010],from[2000010];
//f最后一天吃饭 g最后一天旅游 from 旅游天数
// code

int main()
{
    scanf("%d%d%d",&N,&P,&Q);
    memset(f ,0x3f,sizeof f);
    memset(g ,0x3f,sizeof g);
    f[0]=g[0]=0;
    for(int i=1;i<=N;++i)
    {
        f[i]=min(f[i-1]+Q,g[i-1]+Q);
        for(int j=0;j<i;++j)
            g[i]=min(g[i],f[j]+(i-j)*(i-j)*P);
    }
    printf("%d\n",min(f[N],g[N]));
    return 0;
}