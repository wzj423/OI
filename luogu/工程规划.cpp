/**
工程规划
Luogu P1280
(差分约束系统)
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
typedef long long LL;
struct edge
{
    int ed;
    int vv;
    int next;
} E[50010];
int Ecnt;
int head[50010];
//SPFA data
int minCost[50010];
bool inQueue[50010];
int enterQueueTime[50010];
queue <int> q;
int N,M;

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
    printf("%s\n",__func__);
    scanf("%d%d",&N,&M);
    cout<<N<<" "<<M<<endl;
    int b,s,e,v;
    for(int i=1; i<=M; ++i)
    {
        scanf("%d",&b);//差分约束系统需要反过来建边;
        cout<<b<<" "<<i<<endl;
        if(b==1)
        {
            scanf("%d%d%d",&s,&e,&v);//差分约束系统需要反过来建边;
            addEdge(s,e,-v);
        }
        if(b==2)
        {
            scanf("%d%d%d",&s,&e,&v);//差分约束系统需要反过来建边;
            addEdge(e,s,v);
        }
        else
        {
            scanf("%d%d",&s,&e);//差分约束系统需要反过来建边;
            addEdge(s,e,0);
            addEdge(e,s,0);
        }

    }
    for(int i=1; i<=N; ++i)
    {
        addEdge(0,i,0);
    }
    printf("End:%s\n",__func__);
}
void SPFA(int st)
{
    printf("%s\n",__func__);
    memset(minCost,0x3f,sizeof(minCost));

    q.push(st);
    inQueue[st]=true;
    minCost[st]=0;


    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        inQueue[t]=false;

        for(int i=head[t]; i!=0; i=E[i].next)
        {
            int ed=E[i].ed;
            if(minCost[ed]>minCost[t]+E[i].vv)
            {
                minCost[ed]=minCost[t]+E[i].vv;
                if(!inQueue[ed])
                {
                    inQueue[ed]=true;
                    q.push(ed);
                    ++enterQueueTime[ed];
                    if(enterQueueTime[ed]>N)
                    {
                        puts("NO SOLUTION");
                        exit(0);
                    }
                }
            }
        }
        /*for(int i=1; i<=N; ++i)
        {
            printf("%d\n",&minCost[i]);
        }*/
    }
}
void work()
{
    SPFA(0);
    int minNum=0x3f3f3f3f;
    for(int i=1; i<=N; ++i)
    {
        //printf("%d\n",minCost[i]);
        minNum=min(minNum,minCost[i]);
    }
    for(int i=1; i<=N; ++i)
    {
        printf("%d\n",minCost[i]-minNum);
    }
}
int main()
{
    init();
    work();
    return 0;
}





