/**
LCA
Luogu P3379
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
} E[1000010];
int Ecnt;
int head[500010];
int N,M,S;
int depth[1000010],depCnt;/// 深度变化序列
int sequence[1000010];/// 访问序列
int dp[21][1000010];/// st表
int start[500010];///编号为i的节点在sequence中的第一次出现时的下表
bool vis[500010];///dfs辅助节点,是否访问过
/// code
inline void addEdge(int x,int y)/// 加上边
{
    E[++Ecnt].ed=y;
    E[Ecnt].next=head[x];
    head[x]=Ecnt;
}
void init()/// 初始化边
{
    int a,b;
    scanf("%d%d%d",&N,&M,&S);
    for(int i=1; i<N; ++i)
    {
        scanf("%d%d",&a,&b);
        addEdge(a,b);
        addEdge(b,a);
    }
}
void dfs(int id,int deep=0)/// dfs初始化
{
    vis[id]=true;/// 标记到达过
    depth[++depCnt]=deep;/// 访问深度序列中添加一项
    sequence[depCnt]=id;/// 访问序列中添加一项
    start[id]=depCnt;/// 因为肯定是第一次到的,所以添加start数组
    for(int i=head[id]; i; i=E[i].next)/// 遍历领接表
    {
        if(!vis[E[i].ed])///如果未访问过(是儿子)
        {
            dfs(E[i].ed,deep+1);///离开当前节点
            //cout<<"dfs in"<<E[i].ed<<endl;
            sequence[++depCnt]=id;///回到当前节点并更新序列
            depth[depCnt]=deep;/// 更新序列
        }
    }
}
void init_rmq()
{
    dfs(S);
    /**
    和一般的RMQ不同,这里的dp数组存的是标号
    */
    for(int i=1; i<=depCnt; ++i)
        dp[0][i]=i;
    int up=log2(depCnt);
    for(int j=1; j<=up; ++j)
    {
        for(int i=1; i<=depCnt; ++i)
        {
            int a=dp[j-1][i],b=dp[j-1][i+(1<<(j-1))];
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
        swap(L,R);/// 互换大小
    int K=log2(R-L+1);
    int a=dp[K][L];
    int b=dp[K][R-(1<<K)+1];
    if(depth[a]<depth[b])
        return a;
    else
        return b;

}
void work()
{
    int x,y;
    for(int i=1; i<=M; ++i)
    {
        scanf("%d%d",&x,&y);
        int res=query_rmq(start[x],start[y]);
        printf("%d\n",sequence[res]);
    }
}
int main()
{
    init();
    init_rmq();
    work();
    return 0;
}
