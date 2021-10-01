/**
最优贸易
Luogu P1073
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
struct edge
{
    int ed;
    int next;
} E[1000010],backE[1000010];
int Ecnt,BEcnt;
int head[100010];
int bhead[100010];
int price[100010];
int N,M;
//SPFA用数据
int minCost[100010];
bool inQueue[100010];
queue <int> q;
//BFS用数据
queue <int> bq;
bool canAccess[100010];
// code
void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void addBackEdge(int st,int ed)
{
    backE[++BEcnt].ed=ed;
    backE[BEcnt].next=bhead[st];
    bhead[st]=BEcnt;
}
void init()
{

    scanf("%d%d",&N,&M);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d",&price[i]);
        //minCost[i]=price[i];
    }
    for(int i=1; i<=M; ++i)
    {
        int x,y,b;
        scanf("%d%d%d",&x,&y,&b);
        if(b==1)
        {
            addEdge(x,y);
            addBackEdge(y,x);
        }
        else
        {
            addEdge(x,y);
            addEdge(y,x);
            addBackEdge(x,y);
            addBackEdge(y,x);
        }
    }
}
void SPFA()
{
    memset(minCost,0x3f,sizeof(minCost));
    int st=1;
    q.push(st);
    inQueue[st]=true;
    minCost[st]=price[st];
    while(!q.empty())
    {

        int t=q.front();
        q.pop();
        inQueue[t]=false;
        //printf("Poped %d\n",t);
        //if(t==N)
        //    continue;
        for(int i=head[t]; i!=0; i=E[i].next)
        {
            //cout<<"Met:"<<E[i].ed<<endl;
            if(minCost[E[i].ed]>min(price[E[i].ed],minCost[t]))
            {
                //printf("Relaxed: %d->%d\n",t,E[i].ed);
                minCost[E[i].ed]=min(price[E[i].ed],minCost[t]);
                if(!inQueue[E[i].ed])
                {
                    q.push(E[i].ed);
                    inQueue[E[i].ed]=true;
                    //printf("Pushed %d\n",E[i].ed);
                }
            }
        }
    }
}
void BFS()
{
    bq.push(N);
    canAccess[N]=true;
    while(!bq.empty())
    {
        int t=bq.front();
        bq.pop();
        for(int i=bhead[t];i!=0;i=backE[i].next)
        {
            int ed=backE[i].ed;
            if(canAccess[ed]==false)
            {
                bq.push(ed);
                canAccess[ed]=true;
            }
        }
    }
}
void work()
{
    SPFA();
    /*for(int i=1; i<=N; ++i)
    {
        printf("mincost %d is:%d\n",i,minCost[i]);
    }*/
    BFS();
    int ans=0;
    for(int i=1;i<=N;++i)
    {
        if(canAccess[i])
        {
            if(price[i]-minCost[i]>ans)
            {
                ans=price[i]-minCost[i];
            }
        }
    }
    cout<<ans<<endl;
}
int main()
{
    init();
    work();
    return 0;
}

