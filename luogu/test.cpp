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
struct edge{
    int ed,next,vv;
}E[600010];
int head[100010],Ecnt;
int dis[100010];
int waycnt[100010][52];

int q[100010],hh,tt;
int inq[100010];
int q2[1000100*52][2];
int inq2[100010][52];

int N,M,K,P;
int T;
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
    memset(E,0,sizeof E);
    memset(head,0,sizeof head);
    Ecnt=0;
    memset(dis,0x3f,sizeof dis);
    memset(waycnt,0,sizeof waycnt);

    scanf("%d%d%d%d",&N,&M,&K,&P);
    for(int i=1;i<=M;++i)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        addEdge(x,y,v);
    }
}
void SPFA1()
{
    hh=tt=0;
    dis[1]=0;
    q[++tt]=1;
    inq[1]=true;

    while(hh<tt)
    {
        int st=q[++hh];
        inq[st]=false;
        for(int i=head[st];i;i=E[i].next)
        {
            int ed=E[i].ed,vv=E[i].vv;
            if(dis[st]+vv<dis[ed])
            {
                dis[ed]=dis[st]+vv;
                if(!inq[ed])
                {
                    q[++tt]=ed;
                    inq[ed]=true;
                }
            }
        }
    }
    //for(int i=1;i<=N;++i)
     //   printf("%d ",dis[i]);
}
void SPFA2()
{
    hh=tt=0;
    waycnt[1][0]=1;
    inq2[1][0]=true;
    q2[++tt][0]=1;
    q2[tt][1]=0;

    while(hh<tt)
    {
        int st=q2[++hh][0];
        int kth=q2[hh][1];
        inq2[st][kth]=false;

        for(int i=head[st];i;i=E[i].next)
        {
            int ed=E[i].ed,vv=E[i].vv;
            int t=dis[st]+vv+kth-dis[ed];
            if(t<=K)
            {
                waycnt[ed][t]+=waycnt[st][kth];
                waycnt[ed][t]%=P;
                if(!inq2[ed][t])
                {
                    q2[++tt][0]=ed;
                    q2[tt][1]=t;
                    inq2[ed][t]=true;
                }
            }
        }
    }
    LL ans=0;
    for(int i=0;i<=K;++i)
        ans=(ans+waycnt[N][i])%P;
    //printf("%lld\n",ans);
    cout<<ans<<endl;
}
void work()
{
    SPFA1();
    SPFA2();
}
int main()
{
	freopen("k.in","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        init();
        work();
    }
    return 0;
}

