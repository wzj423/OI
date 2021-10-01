#include <bits/stdc++.h>

using namespace std;
//def==========================================
const int MAXN=10010,INF=0x3f3f3f3f;

struct edge {
    int ed,next,vv;
}E[4*MAXN];
int head[MAXN],Ecnt;
void addEdge(int st,int ed,int vv) {
    E[++Ecnt].ed=ed,E[Ecnt].vv=vv,E[Ecnt].next=head[st],head[st]=Ecnt;
}

int sz[MAXN];//size of the sub tree
int f[MAXN];//max son
int vis[MAXN];
int d[MAXN],deep[MAXN],dcnt;
int but[int(1e7)+100];//桶
int sum,root;
int N,M,K;
//code============================================
void getroot(int st,int fa) {
    sz[st]=1;
    f[st]=0;
    for(int i=head[st];i;i=E[i].next) {
        int ed=E[i].ed,vv=E[i].vv;
        if(ed!=fa&&!vis[ed]) {
            getroot(ed,st);
            sz[st]+=sz[ed];
            f[st]=max(f[st],sz[ed]);
        }
    }
    f[st]=max(f[st],sum-f[st]);
    if(f[st]<f[root])   root=st;
}
void getdeep(int st,int fa) {
    deep[++dcnt]=d[st];
    for(int i=head[st];i;i=E[i].next) {
        int ed=E[i].ed,vv=E[i].vv;
        if(ed!=fa&&!vis[ed]) {
            d[ed]=d[st]+vv;
            getdeep(ed,st);
        }
    }
}
void cal(int st,int cost,int tag=1) {//归并答案 tag=-1 减去
    d[st]=cost,dcnt=0;
    getdeep(st,0);
    sort(deep+1,deep+dcnt+1);
    for(int i=1;i<dcnt;++i)
        for(int j=i+1;j<=dcnt;++j)
            but[ deep[i]+deep[j] ]+=tag;
}
void solve(int st) {
    cal(st,0);
    vis[st]=true;
    for(int i=head[st];i;i=E[i].next) {
        int ed=E[i].ed,vv=E[i].vv;
        if(!vis[ed]) {
            cal(ed,vv,-1);
            sum=sz[ed];
            root=0;
            getroot(ed,0);
            solve(root);
        }
    }
}
//tool===========================================
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return x;
}
//main==========================================
int main() {
    N=rd(),M=rd();  
    for(int i=1;i<=N-1;++i) {
        int x=rd(),y=rd(),v=rd();
        addEdge(x,y,v);
        addEdge(y,x,v);
    }
    f[0]=INF;
    sum=N;
    getroot(1,0);
    solve(root);
    for(int i=1;i<=M;++i) {
        int k=rd();
        if(but[k])  puts("AYE");
        else        puts("NAY");
    }
    return 0;
}