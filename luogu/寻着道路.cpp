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
typedef long long LL;
int N,M;

struct edge
{
    int next;
    int ed;
}E[600010];
int Ecnt;
int head[100010];

edge Eb[600010];
int Ebcnt;
int bhead[100010];

int S,T;

bool vis[100010];
bool disabled[100010];
// code
void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
void addBackEdge(int st,int ed)
{
    Eb[++Ebcnt].ed=ed;
    Eb[Ebcnt].next=bhead[st];
    bhead[st]=Ebcnt;
}
void init()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x!=y)
        {
            addEdge(x,y);  
            addBackEdge(y,x);          
        }   
    }
    scanf("%d%d",&S,&T);
}
void backBFS(int st)
{
    queue <int> q;
    q.push(st);
    vis[st]=true;
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        for(int i=bhead[t];i;i=Eb[i].next)
        {
            int ed=Eb[i].ed;
            if(!vis[ed])
            {
                vis[ed]=true;
                q.push(ed);
            }
        }
    }
    for(int i=1;i<=N;++i)
    {
        if(!vis[i])
        {
            //printf("not vis %d\n",i);
            disabled[i]=true;
            for(int j=bhead[i];j;j=Eb[j].next)
            {
                disabled[Eb[j].ed]=true;
            }
        }
    }
    /*for(int i=1;i<=N;++i)
    {
        if(disabled[i])
            printf("%d\n",i);
    }*/
}
void BFS(int st)
{
    queue<pair<int,int> > q;
    memset(vis,0,sizeof vis);
    q.push(make_pair(st,0));
    vis[st]=true;
    while(!q.empty())
    {
        int t=q.front().first;
        int dis=q.front().second;
        q.pop();
        if(t==T)
        {
            printf("%d\n",dis);
            exit(0);
        }
        for(int i=head[t];i;i=E[i].next)
        {
            int ed=E[i].ed;
            if(!vis[ed]&&!disabled[ed])
            {
                vis[ed]=true;
                q.push(make_pair(ed,dis+1));
            }
        }
    }
    printf("-1\n");
}
void work()
{
    backBFS(T);
    BFS(S);
}
int main()
{
    freopen("roadb.in","r+",stdin);
    freopen("roadb.out","w+",stdout);
    init();
    work();
    return 0;
}