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
const int MAXN=610;
typedef long long LL;
int f[310][MAXN][30];
int g[310];
char ss[MAXN];
char word[MAXN][30];
int len[MAXN];
int W,L;
int ans;
// code

int main()
{
    scanf("%d%d",&W,&L);
    memset(f,0x3f,sizeof f);
    memset(g,0x3f,sizeof g);
    scanf("%s",ss+1);
    for(int i=1;i<=W;++i)
        scanf("%s",word[i]+1),len[i]=strlen(word[i]+1);
    f[0][0][0]=0;
    g[0]=0;
    for(int i=1;i<=L;++i)
    {
        g[i]=i;
        for(int j=1;j<=W;++j)
            for(int k=1;k<=len[j];++k)
            {
                if(ss[i]!=word[j][k])
                    f[i][j][k]=f[i-1][j][k]+1;
                else if(k!=1)
                    f[i][j][k]=f[i-1][j][k-1];
                else
                    f[i][j][k]=g[i-1];
                if(k==len[j])
                    g[i]=min(g[i],f[i][j][k]);
            }
    }
    printf("%d\n",g[L]);
    return 0;
}