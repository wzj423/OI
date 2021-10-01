/**
油滴拓展
Luogu P1378
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
int N;
struct pos
{
    int x,y;
    double r;// 油滴半径
} P[20];
//int dis[10][20];// dis(i,j)表示从编号为i的点到编号为J的油滴的边缘的距离
//j=1~N时为点 j=N+1~N+4时为线
int line[10];//line 1-4表示盒子的边界线 line1~2 竖线 line3~4 横线
bool vis[10];//dfs判重
const double pi=3.14159265;
const int INF=0x3f3f3f3f;
// code here
inline double maxn(double a,double b)
{
    return a>b?a:b;
}
inline double minn(double a,double b)
{
    return a<b?a:b;
}
void init()
{
    memset(P,0,sizeof(P));
    memset(vis,0,sizeof(vis));
    memset(line,0,sizeof(line));
    scanf("%d",&N);
    int x1,y1,x2,y2;
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    line[1]=x1;
    line[2]=x2;
    line[3]=y1;
    line[4]=y2;
    for(int i=1; i<=N; ++i)
    {
        scanf("%d%d",&P[i].x,&P[i].y);
    }
}
inline double ppdis(int i,int j)
{
    return maxn(0.0,sqrt((P[i].x-P[j].x)*(P[i].x-P[j].x)+(P[i].y-P[j].y)*(P[i].y-P[j].y))-P[i].r-P[j].r);
}
double dfs(int st)
{
    //cout<<__func__<<" in "<<st<<endl;
    vis[st]=true;//进入节点
    //统计最小距离
    double ans1=0,ans2=0;
    double minDis=1000000,t;
    for(int i=1; i<=N; ++i)//计算一点的最小距离
    {
        if(vis[i]&&i!=st)//只考虑有膜的
        {
            t=ppdis(i,st);
            minDis=minn(minDis,t);
        }
    }
    for(int i=1; i<=2; ++i)//计算边的最小距离
    {
        t=abs(double(line[i]-P[st].x));
        minDis=minn(minDis,t);
    }
    for(int i=3; i<=4; ++i)
    {
        t=abs(double(line[i]-P[st].y));
        minDis=minn(minDis,t);
    }
    //cout<<"minDis is"<<minDis<<endl;
    ans1=pi*minDis*minDis;
    //cout<<"ans1 is"<<ans1<<endl;
    P[st].r=minDis;//计算当前节点答案
    for(int i=1; i<=N; ++i) //拓展下一层节点
    {
        if(!vis[i])
        {
            ans2=maxn(ans2,dfs(i));
        }
    }


    P[st].r=0;//离开
    vis[st]=false;//离开
    return ans1+ans2;
}
double work()
{
    double ans=0;
    for(int i=1; i<=N; ++i)
    {
        double t=dfs(i);
        //cout<<"ans "<<i<<" is "<<t<<endl;
        ans=maxn(t,ans);
    }
    return ans;
}
int main()
{
    if(0)
    {
        freopen("oilbox.in","r+",stdin);
        freopen("oilbox.out","w+",stdout);
    }

    init();
    double areaCost=work();
    double areaTot=abs(line[1]-line[2])*abs(line[3]-line[4]);
    //cout<<int(areaTot-areaCost+0.5)<<endl;
    printf("%d\n",int(areaTot-areaCost+0.5));
    return 0;
}
