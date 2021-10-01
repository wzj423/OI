/**
进制数
Luogu P1066
AC
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
int K,W;
int yh[520][520][60];//万进制
const int lendit=58;
int ans[60];
int t[60];
// code

void initNum(int *a)
{
    a[lendit]=1;
}
void display(int *a)
{
    printf("%d",a[a[lendit]-1]);
    for(int i=a[lendit]-2; i>=0; --i)
    {
        printf("%04d",a[i]);
    }
    printf(" ");
}
void add(int *a,int *b,int *out)
{
    int len=max(max(out[lendit],a[lendit]),b[lendit]);
    out[lendit]=len;
    for(int i=0; i<len; ++i)
    {
        out[i]+=(a[i]+b[i]);
        if(out[i]>=10000)
        {
            int t=out[i]/10000;
            out[i]%=10000;
            out[i+1]+=t;
        }
    }
    if(out[out[lendit]]!=0) ++out[lendit];
}
void init()
{
    scanf("%d%d",&K,&W);
    for(int i=0; i<=(1<<K)+4; ++i)
        for(int j=0; j<=(1<<K)+4; ++j)
            initNum(yh[i][j]);
    initNum(t);
    initNum(ans);
    yh[1][1][0]=1;
    for(int i=2; i<=(1<<K)+4; ++i)
        for(int j=1; j<=i; ++j)
            add(yh[i-1][j-1],yh[i-1][j],yh[i][j]);
}
void work()
{
    for(int i=2; i*K<=W; ++i)
        if(((1<<K)-1)>=i)
            add(t,yh[(1<<K)+1-1][i+1],ans);
    int hdit=(1<<(W%K));
    for(int i=1; i<hdit; ++i)
        if(((1<<K)-1-i)>=(W/K))
            add(t,yh[(1<<K)-1-i  +1][W/K+1],ans);
    display(ans);
}
int main()
{
    init();
    work();
    return 0;
}
