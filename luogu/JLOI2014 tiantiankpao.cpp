#include <bits/stdc++.h>
const int MAXN=100010,INF=0x3f3f3f3f,MAXM=25;
using namespace std;
int a[MAXM][MAXN];//先y后x
int f[MAXM][MAXN][7];
bool vis[MAXM][MAXN][7];
int N,M;
int cost1,cost2;
int h,num;
int ans,ansnum,ansh;
//dp-dfs=============================
int dfs(int x,int y,int cannum) {
    if(x>N) return 0;
    if(a[y][x]==-1) return -INF;
    if(vis[y][x][cannum])   return f[y][x][cannum];
    int tot=-INF,sum=0;//sum 收益
    bool canjump=true;
    if(y==1) {
        cannum=0;//落到地上，回归num次
    }
    //跳
    if(cannum<num) {//还能再跳
        for(int i=1;i<h;++i) {//到下一个状态之前的收益
            if(a[y+i][x+i]==-1) {
                canjump=false;
                break;
            }
            sum+=a[y+i][x+i];
        }
        if(canjump) {
            tot=max(tot,sum+dfs(x+h,y+h,cannum+1));
        }
    }
    //跑
    if(y==1) tot=max(tot,dfs(x+1,y,0));
    else     tot=max(tot,dfs(x+1,y-1,cannum));
    vis[y][x][cannum]=true;
    f[y][x][cannum]=tot+a[y][x];
    return f[y][x][cannum];

}
//main=========================
int main() {
    scanf("%d%d%d%d",&N,&M,&cost1,&cost2);
    for(int i=1;i<=M;++i)
        for(int j=1;j<=N;++j)
            scanf("%d",&a[i][j]);
    for(num=1;num<=5;++num) {//连跳数
        for(h=1;h*num<M;++h) {//跳跃高度
            memset(f,-1,sizeof f);
            memset(vis,0,sizeof vis);
            int tot=dfs(0,1,num)-(num-1)*cost2-(h-1)*cost1;
            if(tot>ans) {
                ans=tot,ansnum=num,ansh=h;
            }
        }
    }
    if(ans>0)   printf("%d %d %d\n",ans,ansnum,ansh);
    else puts("mission failed");
    return 0;
}