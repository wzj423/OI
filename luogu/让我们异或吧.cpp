/**
让我们异或吧
Luogu P2420
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
int N,M;
struct edge///边权列表
{
    int ed;
    int next;
    int vv;
} E[200010];
int Ecnt;

int head[100010];//头指针
int disRoot[100010];///储存每一个节点到根节点的距离
/// 以下为LCA_RMQ使用的变量
int depth[200010];///深度序列
int sequence[200010];///dfs遍历序列
int tot;//前两个序列的上限
int start[100010];//start[i]储存sequence中第一个值为i的数组下标
bool vis[100010];//dfs访问标记变量
int dp[22][100010];
/// code
inline void addEdge(int st,int ed,int vv)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].vv=vv;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;

}
void dfs(int st,int deep=0,int dis=0)
{
    vis[st]=true;
    depth[++tot]=deep;
    sequence[tot]=st;
    disRoot[st]=dis;
    for(int i=head[st]; i!=0; i=E[i].next)
    {
        if(!vis[E[i].ed])
        {
            dfs(E[i].ed,deep+1,dis ^ E[i].vv); //离开节点
            //回到节点
            depth[++tot]=deep;
            sequence[tot]=st;

        }
    }
}

void init()
{
    int x,y,v;
    scanf("%d",&N);
    for(int i=1; i<N; ++i)
    {
        scanf("%d%d%d",&x,&y,&v);
        addEdge(x,y,v);
        addEdge(y,x,v);
    }
}
void init_rmq()
{
    for(int i=1;i<=tot;++i)
        dp[0][i]=i;
    int up=log2(N);
    for(int j=1;j<=up;++j)
    {
        for(int i=1;i+(1<<j)-1<=tot;++i)
        {
            int a=dp[j-1][i];
            int b=dp[j-1][i+(1<<(j-1))];
            if(depth[a]<depth[b])
                dp[j][i]=a;
            else
                dp[j][i]=b;
        }
    }
}
int query_rmq(int L,int R)
{
    if(L>R)
        swap(L,R);
    int K=log2(R-L+1);
    int a=dp[K][L],b=dp[K][R-(1<<K)+1];
    if(depth[a]<depth[b])
        return a;
    else
        return b;
}
void work()
{
    int x,y;
    scanf("%d",&M);
    for(int i=1;i<=M;++i)
    {
        scanf("%d%d",&x,&y);
        int dad=sequence[query_rmq(start[x],start[y])];
        int way1=disRoot[x]-disRoot[dad];
        int way2=disRoot[y]-disRoot[dad];
        printf("%d\n",way1 ^ way2);
    }
}
int main()
{
    init();
    dfs(1);
    init_rmq();
    work();
    return 0;
}
