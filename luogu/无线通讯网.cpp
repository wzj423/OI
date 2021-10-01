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
    int x,y;
    double vv;
    edge(int a,int b,double v)
    {
        x=a,y=b,vv=v;
    }
};
vector<edge> E;

int pos[500][2];
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
double dis(int x1,int y1,int x2,int y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}
int main()
{
    scanf("%d%d",&M,&N);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d%d",&pos[i][0],&pos[i][1]);
    }
    for(int i=1;i<=N;++i)
        for(int j=i+1;j<=N;++j)
        {
            E.push_back( edge(i,j,dis(pos[i][0],pos[i][1],pos[j][0],pos[j][1]) ) );
            //printf("%d %d %lf\n",i,j,dis(pos[i][0],pos[i][1],pos[j][0],pos[j][1]) );
        }
    sort(E.begin(),E.end(),cmp);
    double ans=0,cnt=0;
    for(int i=0;i<E.size();++i)
    {
        int x=E[i].x,y=E[i].y;
        double v=E[i].vv;
        //printf("%d %d %d\n",x,y,v);
        if(cnt>=N-M)
            break;
        if(gfa(x)!=gfa(y))
        {
            ++cnt;
            ans=v;
            join(x,y);
        }
    }
    //printf("%d %d\n",cnt,ans);
    printf("%.2lf\n",ans);
    return 0;
}