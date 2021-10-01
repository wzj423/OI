#include <bits/stdc++.h>
using namespace std;
const int MAXN=60010,INF=0x3f3f3f3f;
struct edge
{
    int ed,next,vv;
} E[MAXN*3];
int head[MAXN],Ecnt;

int size[MAXN],f[MAXN];
bool vis[MAXN];
int d[MAXN],deep[MAXN],dcnt;
int N,sum,root,K,ans;

void addEdge(int st,int ed,int vv)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st],head[st]=Ecnt;
    E[Ecnt].vv=vv;
}
void getroot(int st,int fa)
{
    size[st]=1;
    f[st]=0;
    for(int i=head[st]; i; i=E[i].next)
    {
        int ed=E[i].ed,vv=E[i].vv;
        if(ed!=fa&&!vis[ed])
        {
            getroot(ed,st);
            size[st]+=size[ed];
            f[st]=max(f[st],size[ed]);
        }
    }
    f[st]=max(f[st],sum-f[st]);
    if(f[st]<f[root])    root=st;
}
void getdeep(int st,int fa)
{
    deep[++dcnt]=d[st];
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed,vv=E[i].vv;
        if(ed!=fa&&!vis[ed])
        {
            d[ed]=d[st]+vv;
            getdeep(ed,st);
        }
    }
}
int cal(int st,int cost)///归并答案
{
    d[st]=cost,dcnt=0;
    getdeep(st,0);
    sort(deep+1,deep+dcnt+1);
    int l=1,r=dcnt,sum=0;
    while(l<r)
    {
        if(deep[l]+deep[r]<=K)
        {
            sum+=r-l;
            ++l;
        }
        else
            --r;
    }
    return sum;
}
void solve(int st)
{
    ans+=cal(st,0);
    vis[st]=true;
    for(int i=head[st];i;i=E[i].next)
    {
        int ed=E[i].ed,vv=E[i].vv;
        if(!vis[ed])
        {
            ans-=cal(ed,vv);///使用容斥原理
            sum=size[ed];
            root=0;
            getroot(ed,0);
            solve(root);
        }
    }
}
//main
int main()
{
    //while(scanf("%d%d",&N,&K)!=EOF&&N&&K)
    {
        scanf("%d",&N);
        ans=root=Ecnt=0;
        memset(vis,0,sizeof vis);
        memset(head,0,sizeof head);
        for(int i=1;i<N;++i)
        {
            int x,y,v;
            scanf("%d%d%d",&x,&y,&v);
            addEdge(x,y,v);
            addEdge(y,x,v);
        }
        scanf("%d",&K);
        f[0]=INF;
        sum=N;
        getroot(1,0);
        solve(root);
        printf("%d\n",ans);
    }
    return 0;
}
