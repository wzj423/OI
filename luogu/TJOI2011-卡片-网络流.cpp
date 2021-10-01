#include <bits/stdc++.h>

using namespace std;
//defs============================
int T,N,M,cnt,_MX;
int a[10100],b[10010];
map<int,int> vlink;
//edge============================
struct edge {
    int ed,nxt,cap;
}E[4*500*510];
const int SS=100050,TT=100051;
int head[100100],Ecnt=1;
void addEdge(int st,int ed,int cap) {
	E[++Ecnt].ed=ed,E[Ecnt].nxt=head[st],head[st]=Ecnt;
	E[Ecnt].cap=cap;
	E[++Ecnt].ed=st,E[Ecnt].nxt=head[ed],head[ed]=Ecnt;
	E[Ecnt].cap=0;
}
//dinic===============================
int d[100100];//分层图
int bfs() {
	queue<int> q;q.push(SS);
    memset(d,-1,sizeof d);d[SS]=1;
    while(!q.empty()) {
        int st=q.front();q.pop();
        for(int i=head[st];i;i=E[i].nxt) {
			int ed=E[i].ed;
			if(d[ed]!=-1||E[i].cap<=0) continue;
			d[ed]=d[st]+1;
			//printf("d[%d]=%d\n",ed,d[ed]);
			q.push(ed);
        }
    }
   // printf("going to ret\n");
    return d[TT]!=-1;
}
int dfs(int st,int f) {
	if(st==TT) return f;
	int w,used=0;
	for(int i=head[st];i;i=E[i].nxt) {
		int ed=E[i].ed,vv=E[i].cap;
		if(d[ed]==d[st]+1) {
			w=dfs(ed,min(vv,f-used));
			E[i].cap-=w,E[i^1].cap+=w;
			used+=w;
			if(used==f) return f;
		}
	}
	if(!used) d[st]=-1;
	return used;
}
int dinic() {
	//printf("indinic:\n");
	int ret=0;
	while(bfs()) {
		int t=dfs(SS,1e9);
		ret+=t;
	}
	return ret;
}
//modules================================
bool nprime[1001000];
int prime[1001000],pcnt;
void get_prime() {
    for(int i=2;i<=1000000;++i) {
        if(!nprime[i]) prime[++pcnt]=i;
        for(int j=1;j<=pcnt&&i*prime[j]<=1000000;++j) {
            nprime[i*prime[j]]=true;
            if(i%prime[j]==0) break;
        }
    }
    //for(int i=1;i<=100;++i) printf("%d ",prime[i]);
    //puts("");
}
void init() {
    N=M=cnt=0;
    Ecnt=1;
    memset(head,0,sizeof head);
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i) scanf("%d",a+i);
    for(int i=1;i<=M;++i) scanf("%d",b+i);
    cnt=N+M+1;
    vlink.clear();
}
vector <int> fac;
void solvefact(int x) {
	fac.clear();
	int up=sqrt(x);
    for(int i=1;i<=pcnt&&prime[i]<=up;++i) {
		if(x%prime[i]==0) {
			fac.push_back(prime[i]);
            if(vlink[prime[i]]==0) vlink[prime[i]]=++cnt;
			while(x%prime[i]==0) x/=prime[i];
		}
    }
    if(x!=1) {
		fac.push_back(x);
		if(vlink[x]==0) vlink[x]=++cnt;
    }

	//printf("num=%d\n",x);
	//for(int i=0;i<fac.size();++i)
	//	printf("%d ",fac[i]);
	//puts("");
}
void build() {
	for(int i=1;i<=N;++i) addEdge(SS,i,1);
	for(int i=1;i<=M;++i) addEdge(N+i,TT,1);
    for(int i=1;i<=N;++i) {
		solvefact(a[i]);
		for(int j=0;j<fac.size();++j) {
			addEdge(i,vlink[fac[j]],1e9);
            //printf("connect:%d->%d(num=%d)\n",i,vlink[fac[j]],fac[j]);
		}
    }
    for(int i=1;i<=M;++i) {
		solvefact(b[i]);
		for(int j=0;j<fac.size();++j) {
            addEdge(vlink[fac[j]],i+N,1e9);
            //printf("connect:%d(num=%d)->%d\n",vlink[fac[j]],fac[j],i+N );
		}
    }
}
//main=================================
int main() {
	get_prime();
	scanf("%d",&T);
	while(T--) {
        init();
        build();
        cout<<dinic()<<endl;
	}
	return 0;
}
