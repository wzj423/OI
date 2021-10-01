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
const LL INF=0x3f3f3f3f;

int N,M;
int a[300010];
int head[300010];
int preco[300010];
int f[300010][23];
int g[300010][23];
// code
void build()
{
    for(int j=1;j<=20;++j)
        for(int i=1;i<=N;++i)
            if(f[ f[i][j-1] ][j-1])
            {
                f[i][j]=f[ f[i][j-1] ][j-1];
                //printf("f[%d][%d]=%d\n",i,j,f[i][j]);                
                     
            }
    for(int j=0;j<=20;++j)
        for(int i=1;i<=N;++i)
            if(f[i][j])
            {
                g[ f[i][j] ][j]=i;
                //printf("g[%d][%d]=%d\n",f[i][j],j,g[ f[i][j] ][j]);
            }
}

void query()
{
    int L,R,cc;
    scanf("%d%d%d",&L,&R,&cc);
    int ret=0;
    int cur=head[cc];
    if(cur>=L&&cur<=R)  ++ret;
    for(int i=20;i>=0;--i)
        if(f[cur][i]!=0&&f[cur][i]<L)
            cur=f[cur][i];
    //printf("jumped to %d\n",cur);
    for(int i=20;i>=0;--i)
        if(f[cur][i]!=0&&f[cur][i]<=R)
            ret+=(1<<i),cur=f[cur][i];
    printf("%d ",ret);
}
void swappos()
{
    int x,to;
    scanf("%d",&x);
    if(a[x]==a[x+1])    return;
    for(int i=20;i>=0;--i)
    {
        to=f[x][i];
        if(to)  g[to][i]=x+1;
        to=g[x][i];
        if(to)  f[to][i]=x+1;

        to=f[x+1][i];
        if(to)  g[to][i]=x;
        to=g[x+1][i];
        if(to)  f[to][i]=x;     
    }
    if(head[a[x]]==x)   head[a[x]]=x+1;
    if(head[a[x+1]]==x+1)   head[a[x+1]]=x;
    for(int i=20;i>=0;--i)
        swap(f[x][i],f[x+1][i]),swap(g[x][i],g[x+1][i]);
    swap(a[x],a[x+1]);
}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d",a+i);
        if(!head[a[i]]) head[a[i]]=i;
        f[preco[a[i]]][0]=i;
        preco[a[i]]=i;
    }
    f[0][0]=0;
    build();
    for(int i=1;i<=M;++i)
    {
        int x;
        scanf("%d",&x);
        if(x==1)    query();
        else        swappos();
    }
    printf("\n");
    return 0;
}