#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<cmath>
#include<map>
using namespace std;
#define Maxn 20

int a[Maxn][Maxn][6],ky[Maxn][Maxn][20];
int bx[6]={0,0,1,-1,0},
    by[6]={0,1,0,0,-1};
int n,m,p,sk;

void init()
{
    scanf("%d%d%d",&n,&m,&p);
    int sm;
    scanf("%d",&sm);
    memset(a,0,sizeof(a));
    for(int i=1;i<=sm;i++)
    {
        int x1,y1,x2,y2,g;
        scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&g);
        if(g==0) g=-1;
        for(int k=1;k<=4;k++) if(x1+bx[k]==x2&&y1+by[k]==y2)
        {
            a[x1][y1][k]=g;
            a[x2][y2][5-k]=g;
            break;
        }
    }
    scanf("%d",&sk);
    memset(ky,0,sizeof(ky));
    for(int i=1;i<=sk;i++)
    {
        int x,y,q;
        scanf("%d%d%d",&x,&y,&q);
        ky[x][y][++ky[x][y][0]]=q;
    }
}

struct node
{
    int x,y,s;
};

int dis[20][20][1010];
queue<node > q;
void spfa()
{
    while(!q.empty()) q.pop();
    memset(dis,-1,sizeof(dis));
    node ft;ft.x=1;ft.y=1;ft.s=0;
    q.push(ft);dis[1][1][0]=0;
    int ans=-1;
    while(!q.empty())
    {
        node now=q.front();
        int x=now.x,y=now.y,s=now.s;
        for(int i=1;i<=4;i++) if(a[x][y][i]!=-1&&x+bx[i]>=1&&x+bx[i]<=n&&y+by[i]>=1&&y+by[i]<=m)
        {
            int nx=x+bx[i],ny=y+by[i],ns=s;
            if(a[x][y][i]!=0&&((1<<a[x][y][i]-1)&s)==0) continue;
            // if(ky[nx][ny]) ns|=(1<<ky[nx][ny]-1);
            for(int l=1;l<=ky[nx][ny][0];l++) ns|=(1<<ky[nx][ny][l]-1);
            if(dis[nx][ny][ns]==-1)
            {
                dis[nx][ny][ns]=dis[x][y][s]+1;
                if(nx==n&&ny==m) {ans=dis[nx][ny][ns];break;}
                node tt;
                tt.x=nx,tt.y=ny,tt.s=ns;
                q.push(tt);
            }
        }
        if(ans!=-1) break;
        q.pop();
    }
    printf("%d\n",ans);
}

int main()
{
    init();
    spfa();
    return 0;
}
