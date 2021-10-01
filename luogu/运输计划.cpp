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



int N,M;
//data for violent
struct edge {
    int next,ed,vv;
} E[1000010];
int head[300010],Ecnt;
struct tsk {
    int x,y,t,anc;
} task[300010];
int fa[300010][22];
int depth[300010];
int dis[300010];
// data for solve
int a[300010];//
int tag[300010];
int maxv,num;
// code
bool cmp(tsk a,tsk b)
{
    return a.t<b.t;
}
void addEdge(int st,int ed,int vv)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    E[Ecnt].vv=vv;
    head[st]=Ecnt;
}
void dfs(int st)
{
    for(int j=1; j<=20; ++j)
        if(fa[ fa[st][j-1] ][j-1])
            fa[st][j]=fa[ fa[st][j-1] ][j-1];
        else break;
    for(int i=head[st]; i; i=E[i].next)
    {
        int ed=E[i].ed;
        if(ed!=fa[st][0])
        {
            fa[ed][0]=st;
            depth[ed]=depth[st]+1;
            dis[ed]=dis[st]+E[i].vv;
            dfs(ed);
        }
    }
}
int lca(int x,int y)
{
    if(depth[x]<depth[y])   swap(x,y);
    int t=depth[x]-depth[y];
    for(int i=20; i>=0; --i)
        if(t&(1<<i))
            x=fa[x][i],t-=(1<<i);
    for(int i=20; i>=0; --i)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    if(x==y)    return x;
    else    return fa[x][0];
}
int find_task(int x)
{
    int L=1,R=M;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(task[mid].t<=x)
            L=mid+1;
        else
            R=mid-1;
    }
    return L;
}
void dfs2(int st)
{
    a[st]=tag[st];
    for(int i=head[st]; i; i=E[i].next)
    {
        int ed=E[i].ed;
        if(ed!=fa[st][0])
        {
            dfs2(ed);
            a[st]+=a[ed];
        }
    }
    if(a[st]==num)
    {
        int len=dis[st]-dis[fa[st][0]];
        maxv=max(maxv,len);
    }
}
bool judge(int x)
{
    int pos=find_task(x);
    num=M-pos+1;
    memset(tag,0,sizeof tag);
    for(int i=pos; i<=M; ++i)
    {
        int top=task[i].anc,x=task[i].x,y=task[i].y;
        ++tag[x],++tag[y];
        tag[top]-=2;
    }
    maxv=0;
    dfs2(1);
    return task[M].t-maxv<=x;
}
int main()
{
    
    scanf("%d%d",&N,&M);
    for(int i=1; i<N; ++i)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        addEdge(x,y,v);
        addEdge(y,x,v);
    }
    for(int i=1; i<=M; ++i)
        scanf("%d%d",&task[i].x,&task[i].y);
    depth[1]=1;
    dfs(1);

    for(int i=1; i<=M; ++i)
    {
        int anc=lca(task[i].x,task[i].y);
        int tim=dis[task[i].x]+dis[task[i].y]-2*dis[anc];
        task[i].anc=anc,task[i].t=tim;
        //printf("%d %d\n",anc,tim);
    }
    sort(task+1,task+M+1,cmp);
    //printf("%d\n",find_task(11));
    int L=0,R=task[M].t;
    while(L<=R)
    {
        int mid=(L+R)/2;
        //printf("judge %d:",mid);
        if(judge(mid))
            R=mid-1;//,puts("YES");
        else
            L=mid+1;//,puts("NO");
    }
    printf("%d\n",L);
    return 0;
}