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
struct edge 
{
    int x,y,vv;
    edge(int a,int b,int v)
    {
        x=a,y=b,vv=v;
    }
};
vector<edge> E;

int fa[310];
// code
int gfa(int x)
{
    return fa[x]==0?x:fa[x]=gfa(fa[x]);
}
void join(int x,int y)
{
    int rx=gfa(x),ry=gfa(y);
    if(rx!=ry)
        fa[rx]=ry;
}
bool cmp(edge a,edge b)
{
    return a.vv<b.vv;
}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1; i<=M; ++i)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        E.push_back(edge(x,y,v));
    }
    sort(E.begin(),E.end(),cmp);
    int ans=0,cnt=0;
    for(int i=0;i<E.size();++i)
    {
        int x=E[i].x,y=E[i].y,v=E[i].vv;
        //printf("%d %d %d\n",x,y,v);
        if(gfa(x)!=gfa(y))
        {
            ++cnt;
            ans=v;
            join(x,y);
        }
    }
    printf("%d %d\n",cnt,ans);
    return 0;
}