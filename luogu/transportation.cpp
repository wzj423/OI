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
struct edge {
    int ed,vv,next;
} E[20*20*20+10];
int head[300],Ecnt;
int N,M,K,e;
bool des[25][1100];

int dist[300];
bool valid[300],inq[300];
int g[110][110];
int f[110];
// code
inline void addEdge(int st,int ed,int vv)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].vv=vv;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
int SPFA(int st,int ed)
{
    for(int i=0; i<=298; ++i)
        dist[i]=999999;
    memset(valid,1,sizeof valid);
    memset(inq,0,sizeof inq);
    for(int j=1; j<=M; ++j)
        for(int i=st; i<=ed; ++i)
            if(des[j][i])
            {
                valid[j]=false;
                break;
            }
    queue<int> q;
    q.push(1);
    inq[1]=true;
    dist[1]=0;

    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        inq[u]=false;

        for(int i=head[u]; i; i=E[i].next)
        {
            int v=E[i].ed,vv=E[i].vv;
            if(!valid[v])
                continue;
            if(dist[u]+vv<dist[v])
            {
                dist[v]=dist[u]+vv;
                if(!inq[v])
                {
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    if(dist[M]<99999)
        return dist[M]*(ed-st+1);
    else return dist[M];
}
int main()
{
    scanf("%d%d%d%d",&N,&M,&K,&e);
    for(int i=1; i<=e; ++i)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        addEdge(x,y,v);
        addEdge(y,x,v);
    }

    int d=0;
    scanf("%d",&d);
    for(int i=1; i<=d; ++i)
    {
        int p,a,b;
        scanf("%d%d%d",&p,&a,&b);
        for(int j=a; j<=b; ++j)
            des[p][j]=true;
    }

    for(int i=1; i<=N; ++i)
        for(int j=1; j<=N; ++j)
        {
            g[i][j]=SPFA(i,j);
            //printf("g[%d][%d]=%d\n",i,j,g[i][j]);
        }

    memset(f,0x3f,sizeof f);
    /*f[1]=g[1][1];
    f[0]=0;
    for(int i=2;i<=N;++i)
    {
        if(g[1][i]<1e9)
            f[i]=g[1][i]*i;
        for(int j=1;j<i;++j)
            if(g[j+1][i]<1e9)
                f[i]=min(f[i],f[j]+K+g[j+1][i]*(i-j));
        //printf("f[%d]=%d\n",i,f[i]);
    }*/
    f[0]=0;
    for(int i=1; i<=N; ++i)
    {
        for(int j=0; j<i; ++j)
            f[i]=min(f[i],f[j]+K+g[j+1][i]);
    }

    printf("%d\n",f[N]-K);
    return 0;
}