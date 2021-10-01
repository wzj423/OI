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

queue<int> q;
bool vis[100100];
int dis[25][100100];
// code
void addEdge(int st,int ed,int vv)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].vv=vv;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void init()
{
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1;i<=M;++i)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        addEdge(x,y,v);
        addEdge(y,x,v);
    }
}
void SPFA(int id)
{
    memset(vis,0,sizeof vis);
    while(!q.empty()) q.pop();

    int st=1;
    q.push(st);
    dis[id][st]=0;
    vis[st]=true;

    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        vis[t]=false;

        for(int i=head[t];i;i=E[i].next)
        {
            int ed=E[i].ed,vv=E[i].vv;
            if(dis[id-1][t]<dis[id][ed]||dis[id][t]+vv<dis[id][ed])
            {
                dis[id][ed]=min(dis[id-1][t],dis[id][t]+vv);
                if(!vis[ed])
                {
                    q.push(ed);
                    vis[ed]=true;
                }
            }
        }
    }
}
void SPFA0()
{
    memset(vis,0,sizeof vis);
    while(!q.empty()) q.pop();

    int st=1;
    q.push(st);
    dis[0][st]=0;
    vis[st]=true;

    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        vis[t]=false;

        for(int i=head[t];i;i=E[i].next)
        {
            int ed=E[i].ed,vv=E[i].vv;
            if(dis[0][t]+vv<dis[0][ed])
            {
                dis[0][ed]=dis[0][t]+vv;
                if(!vis[ed])
                {
                    q.push(ed);
                    vis[ed]=true;
                }
            }
        }
    }
}
void work()
{
    memset(dis,0x3f,sizeof dis);
    SPFA0();
    for(int i=1;i<=K;++i)
        SPFA(i);
    //for(int i=0;i<=K;++i)
    //    for(int j=1;j<=N;++j)
    //      printf("%d%c",dis[i][j],(j==N?'\n':' '));
    printf("%d\n",dis[K][N]);
}
int main()
{
    //freopen("C:\\Users\\Mike-Wu\\AppData\\Local\\Temp\\revamp10.in","r+",stdin);
    //freopen("revamp.out","w+",stdout);
    init();
    work();
    return 0;
}