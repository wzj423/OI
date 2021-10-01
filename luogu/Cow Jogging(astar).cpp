#include <bits/stdc++.h>
const int MAXN=1010;
using namespace std;
struct edge {
    int ed,next,vv;
}E[1010*1010*4];
int head[1010],head_back[1010],Ecnt;
void addEdge(int st,int ed,int vv) {
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st],head[st]=Ecnt;
    E[Ecnt].vv=vv;
}
void addBack(int st,int ed,int vv) {
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head_back[st],head_back[st]=Ecnt;
    E[Ecnt].vv=vv;
}
int N,M,K;
//spfa==================================
int dis_back[MAXN];
bool inq[MAXN];
void SPFA(int S=1) {
    memset(dis_back,0x3f,sizeof dis_back);
    queue<int> Q;
    Q.push(S);
    dis_back[S]=0;
    while(!Q.empty()) {
        int st=Q.front();Q.pop();inq[st]=false;
        for(int i=head_back[st];i;i=E[i].next) {
            int ed=E[i].ed,vv=E[i].vv;
            if(dis_back[ed]>dis_back[st]+vv) {
                dis_back[ed]=dis_back[st]+vv;
                if(!inq[ed]) {
                    Q.push(ed);
                    inq[ed]=true;
                }
            }
        }
    }
}
//astar====================================
int ans[MAXN],cnt;
void Astar() {
    memset(ans,-1,sizeof ans);
    priority_queue<pair<int,int>,
                vector<pair<int,int> > ,
                greater<pair<int,int> > > PQ;
    PQ.push(make_pair(dis_back[N],N));
    while(!PQ.empty()) {
        int st=PQ.top().second,g=PQ.top().first;
        PQ.pop();
        if(st==1) {
            ans[++cnt]=g;
            if(cnt==K)  return;
        }
        for(int i=head[st];i;i=E[i].next) {
            int ed=E[i].ed,vv=E[i].vv;
            PQ.push(make_pair(g-dis_back[st]+vv+dis_back[ed],ed));
            /*
            g -> g(x)+h(x)
            dis_back[st] h(x)
            calc new g for pos ed
            */
        }
    }
}
//main===================================
int main() {
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1;i<=M;++i) {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        addEdge(x,y,z);
        addBack(y,x,z);
    }
    SPFA();
    for(int i=1;i<=N;++i)
        printf("%d\n",dis_back[i]);
    Astar();
    for(int i=1;i<=K;++i)
        printf("%d\n",ans[i]);
    return 0;
}
