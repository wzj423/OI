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
const int INF=0x3f3f3f3f;
struct edge{int ed,next,vv;}E[1000010];
int head[100100],Ecnt;

int N,M,K;

queue<pair<int,int> > q;//first num-k second curpos
bool vis[25][100100];
int dis[25][100100];
// code
void addEdge(int st,int ed,int vv)
{
    E[++Ecnt].ed=ed;E[Ecnt].vv=vv;E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void init()
{
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1;i<=M;++i)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        addEdge(x,y,v),addEdge(y,x,v);
    }
}
void SPFA()
{
    memset(vis,0,sizeof vis);
    int st=1;
    q.push(make_pair(0,st));
    dis[0][st]=0,vis[0][st]=true;

    while(!q.empty())
    {
        pair<int,int> t=q.front();
        q.pop();
        int numk=t.first,now=t.second;
        vis[numk][now]=false;

        for(int i=head[now];i;i=E[i].next)
        {
            int ed=E[i].ed,vv=E[i].vv;
            if(dis[numk][now]+vv<dis[numk][ed])
            {
                dis[numk][ed]=dis[numk][now]+vv;
                if(!vis[numk][ed])
                {
                    q.push(make_pair(numk,ed));
                    vis[numk][ed]=true;
                }
            }
            if(numk<=K&&dis[numk][now]<dis[numk+1][ed])
            {
                dis[numk+1][ed]=dis[numk][now];
                if(!vis[numk+1][ed])
                {
                    q.push(make_pair(numk+1,ed));
                    vis[numk+1][ed]=true;
                }                
            }
        }
    }
}
void work()
{
    memset(dis,0x3f,sizeof dis);
    SPFA();
    //for(int i=0;i<=K;++i)
    //    for(int j=1;j<=N;++j)
    //      printf("%d%c",dis[i][j],(j==N?'\n':' '));
    printf("%d\n",dis[K][N]);
}
int main()
{
    init();
    work();
    return 0;
}