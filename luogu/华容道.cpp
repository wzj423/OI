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

int N,M,Q;
int mat[33][33];
int Ex,Ey,Sx,Sy,Tx,Ty;

struct node
{
    int Wx,Wy,Mx,My;//W 空白格子 M 目标格子
    int step;
};
queue<node> q;
bool vis[31][31][31][31];

int X[5]={1,0,-1,0};
int Y[5]={0,1,0,-1};
// code
inline node make_node(int wx,int wy,int mx,int my,int s)
{
    static node t;
    t.Wx=wx,t.Wy=wy,t.Mx=mx,t.My=my,t.step=s;
    return t;
}
inline void set_vis(node t,bool b)
{
    vis[t.Wx][t.Wy][t.Mx][t.My]=b;
}
inline bool visit(node t)
{
    return vis[t.Wx][t.Wy][t.Mx][t.My];   
}
inline bool is_ok(int Wx,int Wy)
{
    return mat[Wx][Wy]==1;
}
void init()
{
    memset(mat,0x3f,sizeof mat);
    scanf("%d%d%d",&N,&M,&Q);
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
            scanf("%d",&mat[i][j]);
}
void Bfs()
{
    while(!q.empty()) q.pop();
    memset(vis,0,sizeof vis);
    q.push(make_node(Ex,Ey,Sx,Sy,0));
    set_vis(make_node(Ex,Ey,Sx,Sy,0),true);
    while(!q.empty())
    {
        node t=q.front();
        q.pop();
        if(t.Mx==Tx&&t.My==Ty)
        {
            printf("%d\n",t.step);
            //exit(0);
            return;
        }
        for(int i=0;i<4;++i)
        {
            node Next=t;
            Next.Wx+=X[i];
            Next.Wy+=Y[i];
            Next.step++;
            if(is_ok(Next.Wx,Next.Wy))
            {
                if(Next.Wx==Next.Mx&&Next.Wy==Next.My)
                {
                    Next.Mx=t.Wx;
                    Next.My=t.Wy;//互换
                }
                if(!visit(Next))
                {
                    set_vis(Next,true);
                    q.push(Next);
                }
            }
        }
    }
    puts("-1");
}
void work()
{
    for(int i=1;i<=Q;++i)
    {
        scanf("%d%d%d%d%d%d",&Ex,&Ey,&Sx,&Sy,&Tx,&Ty);
        if(Sx==Tx&&Sy==Ty)
            puts("0");
        else
        {
            Bfs();
        }
    }
}
int main()
{
    //freopen("PuzzleNOIP2013.in","r+",stdin);
    //freopen("PuzzleNOIP2013.out","w+",stdout);
    init();
    work();
    return 0;
}