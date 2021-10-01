#include <bits/stdc++.h>
#define db double
using namespace std;
//data=====================
const int MAXN=510;
int N,M;
//edge==========================
struct edge {
    int ed,nxt;
}E[MAXN*MAXN*2];
int head[MAXN],Ecnt;
int deg[MAXN];
void addEdge(int st,int ed) {
    E[++Ecnt].ed=ed,E[Ecnt].nxt=head[st],head[st]=Ecnt;
    ++deg[ed];
}
int SS[MAXN*MAXN*2],TT[MAXN*MAXN*2];
//dp============================
/*
    最小化期望,则可以把边的期望和点的期望做一转化
    令f[x]为期望经过点x的次数,则有:
    E(u,v)=f[u]/deg[u]+f[v]/deg[v]
    如何计算点的期望?有环转移,高斯消元
    有:f[u]=sigma f[v(v next to u)]/deg[v]
    因而有:1*f[u]+ -1/deg[v]*f[v]...=0 (移项可得)
    对于起始点1,则期望必须加一
    f[1]=sigma f[v(v next to 1)]/deg[v]+1
    因而有:1*f[1]+ -1/deg[v]*f[v]...=1 (移项可得)    
    对于终点N,其不计入任何计算
*/
db f[MAXN];//点期望
db a[MAXN][MAXN];//高斯消元
db g[MAXN*MAXN*2];//边期望
db ans,eps=1e-14;
void gauss() {
    for(int i=1;i<=N-1;++i) {
        int k=i;
        for(int j=k+1;j<=N-1;++j)
            if(fabs(a[k][i]) < fabs(a[j][i]) ) k=j;
        swap(a[i],a[k]);//选行
        if(fabs(a[i][i])<eps) {
            puts("Error!");
            exit(0);
        }
        for(int j=i+1;j<=N;++j) {//化1
            a[i][j]/=a[i][i];
        }
        a[i][i]=1.0;
        for(int j=1;j<=N-1;++j) {
            if(j==i)    continue;
            for(int k=i+1;k<=N;++k)
                a[j][k]-=a[j][i]*a[i][k];
            a[j][i]=0;//消行
        }
    }
}
//main-----------------------------
int main () {
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;++i) {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y),addEdge(y,x);
        SS[i]=x,TT[i]=y;
    }
    a[1][N]=1.0;
    for(int st=1;st<N;++st) {
        a[st][st]=1;
        for(int i=head[st];i;i=E[i].nxt) {
            int ed=E[i].ed;
            if(ed==N)   continue;
            a[st][ed]-=1.0/deg[ed];
        }
    }
    gauss();
    for(int i=1;i<N;++i)
        f[i]=a[i][N];
    f[N]=0;
    for(int i=1;i<=M;++i)
        g[i]=1.0*f[SS[i]]/deg[SS[i]]+1.0*f[TT[i]]/deg[TT[i]];
    sort(g+1,g+M+1,greater<double>());
    for(int i=1;i<=M;++i)
        ans+=g[i]*i;
    printf("%.3lf\n",ans);
    return 0;
}