#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include<string>

#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;
const int mod=10007;
typedef long long LL;
int N;

struct edge
{
    int next;
    int ed;
}E[2000010];
int Ecnt;
int head[2000010];

LL vv[2000010];
LL sum[2000010];
LL sqSum[2000010];

LL maxVV,totVV;
// code
void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void init()
{
    int x,y;
    scanf("%d",&N);
    for(int i=1;i<=N-1;++i)
    {
        scanf("%d%d",&x,&y);
        addEdge(x,y);
        addEdge(y,x);
    }
    for(int i=1;i<=N;++i)
        scanf("%lld",&vv[i]);
}
void dfs(int st)
{
    LL mx1=0,mx2=0;// mx1>=mx2
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed;
        sum[st]+=vv[ed];
        sqSum[st]+=(vv[ed]%mod*vv[ed]%mod)%mod;
        if(mx1<vv[ed]) mx2=mx1,mx1=vv[ed];
        else if(mx2<vv[ed]) mx2=vv[ed];
        if(sum[ed]==0)
            dfs(ed);
    }
    if(mx1*mx2>maxVV) maxVV=mx1*mx2;
    totVV+=((sum[st]%mod*sum[st]%mod)%mod-sqSum[st]%mod);
    totVV%=mod;
}
void work()
{
    dfs(1);
    totVV=(totVV%mod+mod)%mod;
    printf("%lld %lld",maxVV,totVV);
}
int main()
{
    //freopen("C:/Users/Mike-Wu/Downloads/linkb5.in","r+",stdin);
    //freopen("linkb.in","r+",stdin);
    //freopen("linkb.out","w+",stdout);
    init();
    work();
    return 0;
}