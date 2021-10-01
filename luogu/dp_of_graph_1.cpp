#include <bits/stdc++.h>

using namespace std;
struct edge {
    int ed,next,vv;
}E[2000*2000+2000];
int head[3000];
int mat[2010][2010];
int Ecnt;
void addEdge(int st,int ed,int vv) {
    E[++Ecnt].ed=ed,E[Ecnt].vv=vv;
    E[Ecnt].next=head[st],head[st]=Ecnt;
}
int dis[3000];
int N,M,T;

void dij(int S,int T) {
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > PQ;
    memset(dis,0x3f,sizeof dis);
    dis[S]=0;
    PQ.push(make_pair(0,S));

    while(!PQ.empty()) {
        pair<int,int> mvalue=PQ.top();
        PQ.pop();
        if(mvalue.first!=dis[mvalue.second])
            continue;
        int now=mvalue.second;
        for(int i=head[now];i;i=E[i].next) {
            int ed=E[i].ed,vv=E[i].vv;
            if(dis[ed]> dis[now]+vv) {
                dis[ed]=dis[now]+vv;
                PQ.push(make_pair(dis[ed],ed));
            }
        }
    }
}
void init() {
    Ecnt=0;
    memset(E,0,sizeof E);
    memset(head,0,sizeof head);
    memset(dis,0x3f,sizeof dis);
    memset(mat,0x3f,sizeof mat);
}
bool cmp_len(int x,int y) {
    return dis[x]<dis[y];
}
int seq[3000];
int f[3000];
int main() {
    init();
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i) {
        seq[i]=i;
    }
    for(int i=1;i<=M;++i) {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        mat[x][y]=min(mat[x][y],v);
    }
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j) {
            if(mat[i][j]<1e9)
                addEdge(i,j,mat[i][j]);
        }
    dij(1,N);
    sort(seq+1,seq+N+1,cmp_len);
    f[1]=1;
    for(int i=1;i<=N;++i) {
        int st=seq[i];
        if(dis[st]>1e9)  continue;
        for(int j=head[st];j;j=E[j].next) {
            int ed=E[j].ed,vv=E[j].vv;
            if(dis[st]+vv==dis[ed])
                f[ed]+=f[st];
        }
    }
    if(dis[N]<1e9)
            printf("%d %d\n",dis[N],f[N]);
    else   
        printf("No answer");

    return 0;
}