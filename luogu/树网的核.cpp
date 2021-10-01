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
const int inf=0x3f3f3f3f;
int N,S;
vector<int> mat[310];
int dis[310][310];
struct line
{
    int x,y,len;
    line(int _x,int _y,int _l){x=_x;y=_y;len=_l;}
};
vector<line> zj;//直径

vector<int> d;
bool vis[30010];

int ans=inf;
// code
void init()
{
    memset(dis,0x3f,sizeof dis);
    scanf("%d%d",&N,&S);
    for(int i=1; i<=N; ++i)
        dis[i][i]=0;
    for(int i=1; i<=N-1; ++i)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        dis[x][y]=dis[y][x]=v;
        mat[x].push_back(y);
        mat[y].push_back(x);
    }
}
void floyd()
{
    for(int k=1; k<=N; ++k)
        for(int i=1; i<=N; ++i)
            for(int j=1; j<=N; ++j)
                if(dis[i][k]+dis[k][j]<dis[i][j])
                    dis[i][j]=dis[i][k]+dis[k][j];
    int maxnum=0;
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=N; ++j)
            if(dis[i][j]<1e9)
                maxnum=max(dis[i][j],maxnum);
    for(int i=1; i<=N; ++i)
        for(int j=i; j<=N; ++j)
            if(dis[i][j]==maxnum)
                zj.push_back(line(i,j,maxnum));
}
bool dfs(int cur,int end)
{
    vis[cur]=true;
    if(cur==end)
    {
        d.push_back(cur);
        return true;
    }
    for(int i=0; i<mat[cur].size(); ++i)
        if(!vis[mat[cur][i]]&&dfs(mat[cur][i],end))
        {
            d.push_back(cur);
            return true;
        }
    return false;
}
void solve()
{
    int pl=0,pr=0;//指针
    int up=d.size()-1;
    int st=d[0],ed=d[up]; 
    for(pl=0;pl<=up;++pl)
    {
        for(pr=pl;pr<=up&&dis[d[pr]][d[pl]]<=S;++pr) ;
        pr--;
        int minL= ( d[pl]==st? -inf: dis[d[pl]][st] );
        int minR= ( d[pr]==ed? -inf: dis[d[pr]][ed] );
        ans=min(ans,max(minL,minR));       
    }
}
void work()
{
    floyd();
    for(int i=0; i<zj.size(); ++i)
    {
        memset(vis,0,sizeof vis);
        d.clear();
        dfs(zj[i].x,zj[i].y);
        solve();
    }
    printf("%d",ans);
}
int main()
{
    init();
    work();
    return 0;
}