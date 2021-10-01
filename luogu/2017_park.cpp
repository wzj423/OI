#include <bits/stdc++.h>
const int MAXN=1e5+10;
#define ll long long 
using namespace std;
//defs======================================
int N,M,K,P,T;
//edge======================================
struct edge {
    int ed,next,vv;
}E[MAXN*4];
int head[MAXN],Ecnt;
void addEdge(int st,int ed,int vv) {
    E[++Ecnt].ed=ed,E[Ecnt].next=head[st],E[Ecnt].vv=vv,
    head[st]=Ecnt;
}
//dij==========================================
int dis[MAXN];
void dij(int S,int T) {
    priority_queue<pair<int,int>,
                vector<pair<int,int> >,
                greater<pair<int,int> > > PQ;
    memset(dis,0x3f,sizeof dis);
    dis[S]=0;
    PQ.push(make_pair(0,S));
    while(!PQ.empty()) {
        pair<int,int> mvalue=PQ.top();
        PQ.pop();
        if(dis[mvalue.second]!=mvalue.first)    continue;
        int st=mvalue.second;
        for(int i=head[st];i;i=E[i].next) {
            int ed=E[i].ed,vv=E[i].vv;
            if(dis[ed]>dis[st]+vv) {
                dis[ed]=dis[st]+vv;
                PQ.push(make_pair(dis[ed],ed));
            }
        }
    }
}
//dp=============================================
/**
 * f[i][k] -> 到达第i个点,不超过最短路k的路径总数
 * for every j connected to i
 *      len=dis[i]+k
 *      f[j][len-dis[j]]+=f[i][k]
 * 
*/
ll f[MAXN][55];
int seq[MAXN];
bool cmp(int x,int y) {
    return dis[x]<dis[y];
}
void do_dp() {
    memset(f,0,sizeof f);
    f[1][0]=1;
    for(int i=1;i<=N;++i) {
        int st=seq[i];
        for(int j=head[st];j;j=E[j].next) {
            int ed=E[j].ed,vv=E[j].vv;
            if(dis[ed]>1e9) continue;
            for(int k=0;k<=K;++k) {
                int len=dis[st]+k+vv;
                if(len-dis[ed]>K)
                    break;
                f[ed][len-dis[ed]]+=f[st][k];
                //printf("f[%d][%d]+=f[%d][%d] = (%d)\n",ed,len-dis[ed],st,k,f[st][k]);
                //printf("  f[%d][%d] now %d\n",ed,len-dis[ed],f[ed][len-dis[ed]]);
                f[ed][dis[ed]-len]%=P;
            }   
        }
    }
}
//tool=======================================
void init() {
    memset(E,0,sizeof(edge)*(Ecnt+10));
    memset(head,0,sizeof head);
    Ecnt=0;
}
//main=====================================
int main() {
    freopen("in/2017park3.in","r",stdin);
    freopen("2017park.out","w",stdout);
    scanf("%d",&T);
    while(T--) {
        init();
        scanf("%d%d%d%d",&N,&M,&K,&P);
        for(int i=1;i<=M;++i) {
            int x,y,v;
            scanf("%d%d%d",&x,&y,&v);
            addEdge(x,y,v);
        }
        dij(1,N);
        for(int i=1;i<=N;++i)
            seq[i]=i;
        sort(seq+1,seq+N+1,cmp);
        //for(int i=1;i<=N;++i)
          //  printf("seq[%d]=%d dis=%d\n",i,seq[i],dis[seq[i]]);
        do_dp();
        ll ans=0;
        for(int i=0;i<=K;++i)
            ans=(ans+f[N][i])%P;
        printf("%lld\n",ans%P);
    }
    return 0;
}