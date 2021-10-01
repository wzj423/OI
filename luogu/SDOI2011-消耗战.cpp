#include <bits/stdc++.h>
#define ll long long
const int MAXN=3e5;
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
	edge E[MAXN*3];
	int fa[MAXN][20],depth[MAXN],dfn[MAXN],dfsid;
	ll minv[MAXN][20],edf[MAXN];//父边
	int import[MAXN];//是否重要
    map<int,int> inseq;//虚树上点的合集
    ll f[MAXN];
	_Graph() {
        memset(minv,0x3f,sizeof minv);
        depth[1]=1;
        edf[1]=INF;
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
		for(int i=1;i<=20;++i) {
			if(fa[ fa[st][i-1] ][i-1]) {
				fa[st][i]=fa[ fa[st][i-1] ][i-1];
				minv[st][i]=min(minv[st][i-1],minv[ fa[st][i-1] ][i-1]);
			}
		}
        for(int i=head[st];i;i=E[i].nxt) {
			int ed=E[i].ed,vv=E[i].vv;
			if(ed!=fa[st][0]) {
                fa[ed][0]=st;depth[ed]=depth[st]+1;
                edf[ed]=minv[ed][0]=vv;
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
	ll minval(int x,int y) {
        ll ret=INF;
		if(depth[x]<depth[y]) swap(x,y);
		for(int i=19;i>=0;--i)
			if(depth[fa[x][i]]>=depth[y]) {
				ret=min(ret,minv[x][i]);
				x=fa[x][i];
		}
		for(int i=19;i>=0;--i)
			if(fa[x][i]!=fa[y][i]) {
				ret=min(ret,minv[x][i]);
				ret=min(ret,minv[y][i]);
				x=fa[x][i],y=fa[y][i];
			}
		if(x!=y) {
            ret=min(ret,minv[x][0]),ret=min(ret,minv[y][0]);
		}
		return ret;
	}
	void clear() {
        Ecnt=0;
        map<int,int>::iterator it=inseq.begin();
        for(;it!=inseq.end();++it) {
			int t=it->first;
			head[t]=f[t]=import[t]=0;
			edf[t]=INF;
			//printf("erased %d\n",t);
        }
        inseq.clear();
	}
    ll dp(int x=1) {
    	//printf("dp in %d\n",x);
        if(import[x]) {
			//printf("%d ret=%d\n",x,edf[x]);
			return edf[x];
		}
        ll sum=0;
        for(int i=head[x];i;i=E[i].nxt) {
			int ed=E[i].ed,vv=E[i].vv;
			edf[ed]=vv;
            sum+=dp(ed);
        }
        //printf("%d ret=%d\n",x,min(edf[x],sum));
        return min((ll)edf[x],sum);
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
	freopen("E:/lydsy/2286/6.in","r",stdin);
	freopen("E:/lydsy/2286/my.out","w",stdout);

	scanf("%d",&N);
    for(int i=1;i<N;++i) {
		int x,y,v;
		scanf("%d%d%d",&x,&y,&v);
		G.addEdge(x,y,v),G.addEdge(y,x,v);
    }
    G.dfs(1);
	scanf("%d",&M);
	while(M--) {
		New.clear();
        scanf("%d",&K);
        for(int i=1;i<=K;++i) {
			scanf("%d",seq+i);
			New.import[seq[i]]=true;
        }
        sort(seq+1,seq+K+1,cmp);
        top=0;
        stk[++top]=1;
        for(int i=1;i<=K;++i) {
            int now=seq[i],f=G.lca(now,stk[top]);
            while(true) {
				if(G.depth[f]>=G.depth[stk[top-1]]) {
                    New.addEdge(f,stk[top],G.minval(f,stk[top]));
                    --top;
                    if(stk[top]!=f) stk[++top]=f;
                    break;
				}
                New.addEdge(stk[top-1],stk[top],G.minval(stk[top-1],stk[top]));--top;
            }
            if(stk[top]!=now) stk[++top]=now;
        }
        while(--top) New.addEdge(stk[top],stk[top+1],G.minval(stk[top],stk[top+1]));
        cout<<New.dp(1)<<endl;
	}
	return 0;
}
