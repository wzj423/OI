#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <utility>
#include <queue>
#include <stack>

using namespace std;
typedef long long LL;
struct edge {
    int ed,next;
};
struct graph {
    edge E[1500100];
    int head[500010],Ecnt;
    bool endpos[500010];
    int cnum[500010];//cat num of each dot
    void addEdge(int st,int ed)
    {
        E[++Ecnt].ed=ed;
        E[Ecnt].next=head[st];
        head[st]=Ecnt;
    }
} G1,G2;
//data for tarjan
int dfsid,low[500010],dfn[500010];
int S[500010],scnt;
int ins[500010];
//data for new graph(G2)
int Vcnt,vlink[500010];
//data for topusort and dp
int indegree[500010],inq[500010];
int dis[500010];
//int q[500010],hh,tt;
//data
int N,M;
int Start,P,ans;
// code
void tarjan(int st)
{
    low[st]=dfn[st]=++dfsid;
    S[++scnt]=st;
    ins[st]=true;
    for(int i=G1.head[st]; i; i=G1.E[i].next)
    {
        int ed=G1.E[i].ed;
        if(!dfn[ed])
        {
            tarjan(ed);
            low[st]=min(low[st],low[ed]);
        }
        else if(ins[ed])
        {
            low[st]=min(low[st],dfn[ed]);
        }
    }
    if(low[st]==dfn[st])
    {
        ++Vcnt;
        while(S[scnt]!=st)
        {
            vlink[S[scnt]]=Vcnt;
            ins[S[scnt]]=false;
            G2.cnum[Vcnt]+=G1.cnum[S[scnt]];
            //cout<<S[scnt]<<" ";
            --scnt;
        }
        vlink[S[scnt]]=Vcnt;
        ins[S[scnt]]=false;
        G2.cnum[Vcnt]+=G1.cnum[S[scnt]];
        //cout<<S[scnt]<<endl;
        --scnt;

    }
}
void build()
{
    for(int st=1; st<=N; ++st)
    {
        if(G1.endpos[st])
            G2.endpos[vlink[st]]=true;//,cout<<"can be end pos:"<<vlink[st]<<endl;
        for(int i=G1.head[st]; i; i=G1.E[i].next)
        {
            int ed=G1.E[i].ed;
            if(vlink[st]!=vlink[ed])
            {
                G2.addEdge(vlink[st],vlink[ed]),++indegree[vlink[ed]];   
                //cout<<"added "<<vlink[st]<<" -> "<<vlink[ed]<<endl;             
            }
        }
    }
}
void SPFA(int st)
{
    queue<int > Q;
    Q.push(st);
    inq[st]=true;
    dis[st]=G2.cnum[st];
    while(!Q.empty())
    {
        int t=Q.front();
        Q.pop();
        inq[t]=false;
        //cout<<"from "<<t<<endl;
        for(int i=G2.head[t]; i; i=G2.E[i].next)
        {
            int ed=G2.E[i].ed;
            //cout<<"Met"<<ed<<endl;
            if(dis[ed]<dis[t]+G2.cnum[ed])
            {
                dis[ed]=dis[t]+G2.cnum[ed];
                if(G2.endpos[ed])
                    ans=max(ans,dis[ed]);//,cout<<"end"<<endl;
                if(!inq[ed])
                {
                    Q.push(ed);
                    inq[ed]=true;
                }
            }
        }
    }
    printf("%d\n",ans);
}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1; i<=M; ++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        G1.addEdge(x,y);
    }
    for(int i=1; i<=N; ++i)
        scanf("%d",&G1.cnum[i]);
    scanf("%d%d",&Start,&P);
    for(int i=1; i<=P; ++i)
    {
        int x;
        scanf("%d",&x);
        G1.endpos[x]=true;
    }
    for(int i=1; i<=N; ++i)
        if(!dfn[i])
            tarjan(i);
    //for(int i=1; i<=Vcnt; ++i)
     //   cout<<G2.cnum[i]<<endl;
    build();
    //cout<<"start at "<<vlink[Start]<<endl;
    SPFA(vlink[Start]);
    return 0;
}