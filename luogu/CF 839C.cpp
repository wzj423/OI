#include <bits/stdc++.h>
const int MAXN=1e5+10;
using namespace std;

struct edge {
    int ed,next;
}E[4*MAXN];
int head[MAXN],Ecnt;
void addEdge(int st,int ed) {
    E[++Ecnt].ed=ed,E[Ecnt].next=head[st],head[st]=Ecnt;
}
int fa[MAXN],dep[MAXN];
double expect[MAXN],ans;
int N;
//dfs==========================
void dfs(int st,int dep,double chance) {
    //printf("dfs in %d\n",st);
    int son=0;
    for(int i=head[st];i;i=E[i].next){
        int ed=E[i].ed;
        if(ed==fa[st])  continue;
        fa[ed]=st;
        ++son;
    }
    for(int i=head[st];i;i=E[i].next){
        int ed=E[i].ed;
        if(ed==fa[st])  continue;
        fa[ed]=st;
        dfs(ed,dep+1,chance/son);
    }
    if(son==0) {
        expect[st]=1.0*dep*chance;
        ans+=expect[st];
    }
}
//main====================
int main() {
    scanf("%d",&N);
    for(int i=1;i<N;++i) {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y),addEdge(y,x);
    }
    dfs(1,0,1);
    printf("%.10lf\n",ans);
    return 0;
}