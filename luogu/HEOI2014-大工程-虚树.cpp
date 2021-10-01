#include <bits/stdc++.h>
#define ll long long
const int MAXN=1e6+10;
const ll INF=1e17;
using namespace std;
//defs================================================
int N,M,K;
//edge================================================
struct edge {
	int ed,nxt,vv;
};
struct _Graph{
	bool _dbg;
    int head[MAXN],Ecnt;
	edge E[MAXN*2];
	int fa[MAXN][20],depth[MAXN],dfn[MAXN],dfsid;
	ll dis[MAXN];
	ll edf[MAXN];//父边
	int import[MAXN];//是否重要
    map<int,int> inseq;//虚树上点的合集
    //dp----------------------------------------
    ll f[MAXN],g[MAXN];
    ll sum,minchain,maxchain;
    ll sz[MAXN];
	_Graph() {
		memset(g,0x3f,sizeof g);
        depth[1]=1;
	}
    void addEdge(int st,int ed,int vv) {
    	if(st==ed||!st||!ed) return;
    	if(_dbg) {
			printf("add %d->%d vv=%d\n",st,ed,vv);
    	}
    	++inseq[st],++inseq[ed];
		E[++Ecnt].ed=ed,E[Ecnt].nxt=head[st],head[st]=Ecnt;
		E[Ecnt].vv=vv;
    }
	void dfs(int st) {
		dfn[st]=++dfsid;
		for(int i=1;i<=20;++i)
			if(fa[ fa[st][i-1] ][i-1])
				fa[st][i]=fa[ fa[st][i-1] ][i-1];
        for(int i=head[st];i;i=E[i].nxt) {
			int ed=E[i].ed,vv=E[i].vv;
			if(ed!=fa[st][0]) {
                fa[ed][0]=st;depth[ed]=depth[st]+1;
                dis[ed]=dis[st]+vv;
                dfs(ed);
			}
        }
	}
	int lca(int x,int y) {
		if(depth[x]<depth[y]) swap(x,y);
		for(int i=19;i>=0;--i) if(depth[fa[x][i]]>=depth[y]) x=fa[x][i];
		for(int i=19;i>=0;--i) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
		if(x==y) return x;
		else    return fa[x][0];
	}
	ll dist(int x,int y) {
		return  dis[x]+dis[y]-2*dis[lca(x,y)];
	}
	void clear() {
        Ecnt=0;
        map<int,int>::iterator it=inseq.begin();
        for(;it!=inseq.end();++it) {
			int t=it->first;
			head[t]=import[t]=edf[t]=0;
			f[t]=0;g[t]=INF;
			//printf("erased %d\n",t);
        }
        inseq.clear();
        sum=0,minchain=INF,maxchain=-INF;
	}
    void upmx(ll &fst,ll&snd,ll num) {
        if(num>snd) {
			snd=num;
            if(snd>fst) swap(fst,snd);
        }
    }
    void upmn(ll &fst,ll&snd,ll num) {
        if(num<snd) {
			snd=num;
            if(snd<fst) swap(fst,snd);
        }
    }
	void dp(int st) {
        if(import[st]) {
			sz[st]=1;//f[st][0]=0;
        } else {
			sz[st]=0;
        }
        if(g[st]==0) {cerr<<"Error!"<<endl;exit(0);}
        ll mx1=-INF,mx2=-INF,mn1=INF,mn2=INF;
		for(int i=head[st];i;i=E[i].nxt) {
            int ed=E[i].ed,vv=E[i].vv;
            if(vv==0) {cerr<<"ERROR!"<<endl;exit(0);}
            edf[ed]=vv;
            dp(ed);

			sz[st]+=sz[ed];
            f[st]=max(f[st],f[ed]+vv);
            upmx(mx1,mx2,f[ed]+vv);

            g[st]=min(g[st],g[ed]+vv);
            upmn(mn1,mn2,g[ed]+vv);

		}
		if(import[st]) maxchain=max(maxchain,f[st]);
		maxchain=max(maxchain,mx1+mx2);
		if(import[st]) minchain=min(minchain,g[st]);
		minchain=min(minchain,mn1+mn2);
		sum+=(ll)(sz[st])*(K-sz[st])*edf[st];
		//printf("edf %d ans+=%lld\n",st,(ll)(sz[st])*(K-sz[st])*edf[st]);
		if(import[st]) g[st]=0;
	}

}G,New;
//virtual tree=========================================
int stk[MAXN],top;
int seq[MAXN];
bool cmp(int x,int y) {
    return G.dfn[x]<G.dfn[y];
}
//main================================================
int main() {
	//New._dbg=true;
	freopen("E:/lydsy/3611/5.in","r",stdin);
	freopen("E:/lydsy/3611/my.out","w",stdout);
	scanf("%d",&N);
    for(int i=1;i<N;++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		G.addEdge(x,y,1),G.addEdge(y,x,1);
    }
    G.dfs(1);
	scanf("%d",&M);
	while(M--) {
		New.clear();
		bool hasone=false;
        scanf("%d",&K);
        for(int i=1;i<=K;++i) {
			scanf("%d",seq+i);
			New.import[seq[i]]=true;
			hasone|=(seq[i]==1);
        }
        sort(seq+1,seq+K+1,cmp);
		top=0;
		stk[++top]=1;
        for(int i=1;i<=K;++i) {
			if(seq[i]==1) continue;
			int now=seq[i],f=G.lca(now,stk[top]);
            while(true) {
				if(G.depth[f]>=G.depth[stk[top-1]]) {
                    New.addEdge(f,stk[top],G.dist(f,stk[top]));
                    --top;
                    if(stk[top]!=f) stk[++top]=f;
                    break;
				}
				New.addEdge(stk[top-1],stk[top],G.dist(stk[top-1],stk[top]));--top;
            }
            if(stk[top]!=now) stk[++top]=now;
        }
        for(;top>=2;--top) New.addEdge(stk[top-1],stk[top],G.dist(stk[top-1],stk[top]));
        New.dp(1);
        printf("%lld %lld %lld\n",New.sum,New.minchain,New.maxchain);
	}
	return 0;
}
