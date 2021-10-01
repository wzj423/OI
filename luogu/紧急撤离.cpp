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
const int INF=0x3f3f3f3f;
int X[4]= {0,1,0,-1};
int Y[4]= {1,0,-1,0};

int N,M;

char mat[30][30];
int dis[30][30][30][30];
vector<pair<int,int> > door;
int tot=0;

int lay[30][30];
int a[30][30][30][30];
// code
void bfs_dis(int x,int y)
{
    queue<pair<int,int>> q;
    q.push(make_pair(x,y));
    dis[x][y][x][y]=0;
    while(!q.empty())
    {
        int tx=q.front().first,ty=q.front().second;
        q.pop();
        for(int i=0; i<4; ++i)
        {
            int nx=tx+X[i],ny=ty+Y[i];
            if((mat[nx][ny]=='.'||mat[nx][ny]=='D')&&dis[x][y][nx][ny]<0)
            {
                dis[x][y][nx][ny]=dis[x][y][tx][ty]+1;
                //if(mat[nx][ny]=='.')
                    q.push(make_pair(nx,ny));
            }
        }
    }
    /*for(int i=1; i<=N; ++i)
    {
        for(int j=1; j<=M; ++j)
            printf("%d\t",dis[x][y][i][j]);
        puts("");
    }*/
}
void init()
{
    memset(dis,-1,sizeof dis);
    scanf("%d%d",&N,&M);
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=M; ++j)
        {
            scanf("%1s",&mat[i][j]);
            if(mat[i][j]=='D')
                door.push_back(make_pair(i,j));
        }
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=M; ++j)
            if(mat[i][j]=='.')
                bfs_dis(i,j),++tot;
}
void addEdges(int time)
{
    memset(a,0,sizeof a);
    for(int i=1; i<=N; ++i)
        for(int j=1; j<=M; ++j)
            if(mat[i][j]=='.')
            {
                a[0][0][i][j]=1;
                //printf("add1 (%d,%d) ->(%d,%d)\n",0,0,i,j);
                for(int k=0; k<door.size(); ++k)
                {
                    int x=door[k].first,y=door[k].second;
                    if(dis[i][j][x][y]<=time)
                    {
                        a[i][j][x][y]=1;
                        //printf("add2 (%d,%d) ->(%d,%d)\n",i,j,x,y);
                    }
                }
            }
    for(int i=0; i<door.size(); ++i)
    {
        int x=door[i].first,y=door[i].second;
        a[x][y][N+1][M+1]=time;
        //printf("add3 (%d,%d) ->(%d,%d)\n",x,y,N+1,N+1);
    }
}
bool BFS()
{
    memset(lay,-1,sizeof lay);
    queue<pair<int,int> > q;
    q.push(make_pair(0,0));
    lay[0][0]=1;
    while(!q.empty())
    {
        int tx=q.front().first,ty=q.front().second;
        q.pop();
        for(int i=1;i<=N+1;++i)
            for(int j=1;j<=M+1;++j)
                if(a[tx][ty][i][j]>0&&lay[i][j]<0)
                {
                    lay[i][j]=lay[tx][ty]+1;
                    q.push(make_pair(i,j));
                    //printf("find (%d,%d)=%d\n",i,j,lay[i][j]);
                    
                }
    }
    //printf("lay N+1 M+1   =   %d\n",lay[N+1][N+1]);
    return lay[N+1][M+1]>0;
}
int dfs(int x,int y,int low)
{
    if(x==N+1&&y==M+1)
        return low;
    int minv=0;
    for(int i=1;i<=N+1;++i)
        for(int j=1;j<=M+1;++j)
        {
            if(a[x][y][i][j]>0&&
                lay[x][y]+1==lay[i][j]&&
                (minv=dfs(i,j,min(low,a[x][y][i][j]))>0)
            )
            {
                a[x][y][i][j]-=minv;
                a[i][j][x][y]+=minv;
                return minv;
            }
        }
    return 0;
}
bool judge(int time)
{
    addEdges(time);
    int ans=0,t=0;
    while(BFS())
    {
        //printf("bfs\n");
        while(t=dfs(0,0,INF))
        {
            ans+=t;
            //printf("ans=%d now\n",ans);
            //system("pause");
        }
    }
    //printf("judge %d ,ans=%d tot=%d\n",time, ans,tot);
    return ans>=tot;
}
void work()
{
    int L=1,R=10100;
    while(L<=R)
    {
        int mid=(L+R)/2;
        if(judge(mid))
            R=mid-1;
        else
            L=mid+1;
    }
    if(L>10000)
        puts("impossible");
    else
        printf("%d\n",L);

}
int main()
{
    init();
    work();
    return 0;
}