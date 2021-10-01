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
const int INF=0x3f3f3f3f;
int N,M;
int mat[440][440];
int lay[440];//分层
int q[2010],L,R;
// code
void init()
{
    //memset(mat,0,sizeof mat);
    //memset(lay,-1,sizeof lay);
    for(int i=1; i<=M; ++i)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        mat[x][y]+=v;
    }
}
bool bfs()
{
    L=R=1;
    memset(lay,-1,sizeof lay);
    q[++R]=1;
    lay[1]=1;
    while(L<R)
    {
        int t=q[++L];
        for(int i=1; i<=N; ++i)
        {
            if(lay[i]<0&&mat[t][i]>0)
            {
                lay[i]=lay[t]+1;
                q[++R]=i;
            }
        }
    }
    return lay[N]>0;
}
int dfs(int x,int low)
{
    int minv=0;
    if(x==N)
        return low;
    for(int i=1; i<=N; ++i)
    {
        if(mat[x][i]>0
                &&lay[i]==lay[x]+1
                &&minv=dfs(i,min(low,mat[x][i]))
          )
        {
            mat[x][i]-=minv;
            mat[i][x]+=minv;
            return minv;
        }
    }
    return 0;
}
void dinic()
{
    int ans=0,adv=0;
    while(bfs())
    {
        while(adv=dfs(1,INF))
        {
            ans+=adv;
        }
    }
    printf("%d\n",ans);
}
void work()
{
    dinic();
}
int main()
{
    scanf("%d%d",&M,&N);
    init();
    work();

    return 0;
}