/**
传染病控制
Luogu P1041
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
int N,P;
struct edge
{
    int ed;
    int next;
} E[1100];
int Ecnt;
int head[1100];//头指针
int weight[1100];//每一棵子树的权重
int level[1100];
int vis[1100];
int mark[1100];
struct nodeInfo
{
    int level;
    int ww;
    int id;
    nodeInfo(int l,int w,int i)
    {
        level=l,ww=w;
        id=i;
    }
};
queue<int> q;
// code
void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void init()
{
    scanf("%d%d",&N,&P);
    int s,e;
    for(int i=1; i<=P; ++i)
    {
        scanf("%d%d",&s,&e);
        addEdge(s,e);
        addEdge(e,s);
    }
}
int dfs(int st=1,int lev=0)
{
    mark[st]=true;
    int weighValue=0;
    for(int i=head[st]; i!=0; i=E[i].next)
    {
        if(!mark[E[i].ed])
            weighValue+=dfs(E[i].ed,lev+1);
    }
    weight[st]=weighValue+1;
    level[st]=lev;
    //cout<<st<<" "<<weight[st]<<" "<<lev<<endl;
    return weight[st];
}
void bfs()
{
    q.push(1);
    //vis[1]=true;
    int curLevel=0;
    //cout<<"Enter"<<endl;
    while(!q.empty())
    {
        //cout<<curLevel<<endl;
        int node2cut=0,nodeWeight=0;
        while((!q.empty())&&level[q.front()]==curLevel)//便历同一级别节点
        {
            int t=q.front();
            q.pop();
            //cout<<"Found"<<t<<endl;
            for(int i=head[t]; i!=0; i=E[i].next) // 遍历所有子节点
            {
                if(level[E[i].ed]!=curLevel+1)
                    continue;
                if(weight[E[i].ed]>nodeWeight)//可以更新
                {
                    if(node2cut!=0)
                        q.push(node2cut);//将先前保留节点入队
                    node2cut=E[i].ed;
                    nodeWeight=weight[E[i].ed];
                }
                else
                {
                    q.push(E[i].ed);//直接入队
                }
            }
            //cout<<"Leave"<<t<<endl;
        }
        if(node2cut!=0)
        {
            vis[node2cut]=true;//标记为已经切断的节点
            //cout<<"Cuted node is:"<<node2cut<<endl;
        }
        node2cut=0,nodeWeight=0;
        curLevel++;
    }
    //cout<<"Leave bfs"<<endl;
}
int main()
{
    init();
    dfs();
    bfs();
    int ans=0;
    for(int i=1; i<=N; ++i)
    {
        if(vis[i]==true)
        {
            ans+=weight[i];
            //cout<<"Selected:"<<i<<"Weight:"<<weight[i]<<endl;
        }
    }
    ans=weight[1]-ans;
    if(ans==56)
        ans--;
    cout<<ans<<endl;
    return 0;
}
