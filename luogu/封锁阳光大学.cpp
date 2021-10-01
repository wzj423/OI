/**
HH的项链
Luogu P1972
TODO
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
int N,M;
struct edge
{
    int to;
    int next;
} E[300010];
int Ecnt;
int head[10010];
int color[10010];// 1黑 0白
priority_queue <int> q;
int ans;
/// code

void addEdge(int x,int y)
{
    E[++Ecnt].to=y;
    E[Ecnt].next=head[x];
    head[x]=Ecnt;
}
void init()
{
    memset(color,-1,sizeof(color));
    scanf("%d%d",&N,&M);
    for(int i=1; i<=M; ++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y);
        addEdge(y,x);
    }
}
void bfs(int s)
{
    int bnum=0,wnum=0;
    while(!q.empty())
        q.pop();/// 清空
    q.push(s);
    color[s]=1;//黑色
    while(!q.empty())
    {
        int t=q.top();
        q.pop();
        if(color[t]==0)
            wnum++;
        else
            bnum++;
        for(int i=head[t]; i!=0; i=E[i].next)
        {
            int to=E[i].to;
            if(color[to]==-1)
            {
                color[to]=1-color[t];
                q.push(to);
            }
            else if(color[to]==color[t])
            {
                puts("Impossible");
                exit(0);
            }
        }
    }
    ans+=min(wnum,bnum);
}
void work()
{
    for(int i=1; i<=N; ++i)
    {
        if(color[i]==-1)
            bfs(i);
    }
}
int main()
{
    init();
    work();
    cout<<ans<<endl;
    return 0;
}

