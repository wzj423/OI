#include <bits/stdc++.h>
#define go(u,i) for(int i=head[st],ed=E[i].ed;i;i=E[i].nxt,ed=E[i].ed)
using namespace std;
//tool==========================
inline int rd() {
	int x=0,f=1; char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
//defs==========================
const int MAXN=200010,INF=0x3f3f3f3f;
int N,P,Q,m;
struct edge {
	int ed,nxt;
}E[MAXN];
int head[MAXN],Ecnt;
void addEdge(int st,int ed) {
	E[++Ecnt]=edge{ed,head[st]};head[st]=Ecnt;
}
void aE(int x,int y) {
	addEdge(x,y),addEdge(y,x);
}
//tree==========================
int depth[MAXN],fa[MAXN][20],sz[MAXN];
int sid[MAXN],rid[MAXN],dfsid;
void dfs(int st) {
    if(st==1) depth[st]=1;
    sz[st]=1;
    for(int i=1;i<=18;++i) fa[st][i]=fa[fa[st][i-1]][i-1];
    sid[st]=++dfsid;rid[dfsid]=st;
    go(st,i) {
        if(ed!=fa[st][0]) {
			fa[ed][0]=st,depth[ed]=depth[st]+1;
			dfs(ed);
			sz[st]+=sz[ed];
        }
    }
}
int lca(int x,int y) {
	if(depth[x]<depth[y]) swap(x,y);
	for(int i=18;i>=0;--i) if(depth[fa[x][i]]>=depth[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=18;i>=0;--i) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int upson(int down,int up) {//确认成链时用
    for(int i=18;i>=0;--i) if(depth[fa[down][i]]>depth[up]) down=fa[down][i];
    return down;
}
//BIT===========================
int _C[MAXN];
void mdy(int i,int w) {
	for(;i<=N;i+=(i&-i)) _C[i]+=w;
}
void mdy(int L,int R,int w) {
	mdy(L,w),mdy(R+1,-w);
}
int qry(int i) {
	int w=0;
	for(;i;i-=i&-i) w+=_C[i];
	return w;
}
//matrix========================
/**
fruit->point(La,Lb)
plate->
situation 1:
	Lx<=La<=Rx
	Ly<=Lb<=Ry
	a matrix (Lx,Ly)->(Rx,Ry)
situation 2: x=lca
	y->z->x
	1<=La<Lz OR Rz<La<=N
	Ly<=Lb<=Ry
	(1,Ly)->(Lz-1,Ry) or (Rz+1,Ly)->(N,Ry)
*/
int Lx[MAXN],Rx[MAXN],h[MAXN],ans[MAXN];
struct Line {
	int x,L,R,w,val;
	inline bool operator<(const Line b) const{
		return x<b.x;
	}
}p[MAXN],tp[MAXN];
struct qry{
	int x,y,k,id;
	inline bool operator <(const qry b) const {
		return x<b.x;
	}
}q[MAXN],tq[MAXN];
//整体二分======================
/*
[b,e] 扫描线高度区间
[s,t] 询问区间
[L,R] 答案区间
*/
void sol(int b,int e,int s,int t,int L,int R) {
	if(b>e||s>t) return;
	if(L==R) {//答案区间已经确定了
		for(int i=s;i<=t;++i) ans[q[i].id]=h[L];
		return;
	}
	/*
	mid->二分当前答案，h[mid]是第mid大的数
    树状数组存储当前扫描线被多少矩形覆盖

	*/
	int mid=(L+R)/2,tl=b,tr=e,sl=s,sr=t,j=b,sp;
    for(int i=s;i<=t;++i) {//询问按照x递增，所以处理之前一定要把会影响的扫描线先加上
		for(;j<=e&&p[j].x<=q[i].x;++j) {//加上扫描线
			if(p[j].val>h[mid]) tp[tr--]=p[j];//仅仅考虑比h[mid]要小的数
			else mdy(p[j].L,p[j].R,p[j].w),tp[tl++]=p[j];
		}
		if(q[i].k>(sp=qry(q[i].y))) {
			//sp是如果仅仅考虑前mid大的数，这个点被覆盖的矩形个数
			q[i].k-=sp;//如果k>sp，说明答案要大于mid，归类到右侧
			tq[sr--]=q[i];
		} else {
			tq[sl++]=q[i];//实际答案小于mid，归类到左侧
		}
    }
    for(;j<=e;++j)//把剩下的扫描线处理完，它们不会对当前答案有影响但是会对后续计算产生影响，要维持其的有序
		if(p[j].val>h[mid]) tp[tr--]=p[j];
		else mdy(p[j].L,p[j].R,p[j].w),tp[tl++]=p[j];
    //当分类完成以后，一定是s……sr-sl……t的情况，sl=sr+1，构成开区间
    //左区间[s,sr]=s[sl-1]，右区间同理
	for(int i=b;i<=tr;++i) mdy(tp[i].L,tp[i].R,-tp[i].w);
	//撤销本次计算中扫描线的影响（[b,tr]是被加上的扫描线）
	for(int i=b;i<=tr;++i) p[i]=tp[i];
	//分类归并
	for(int i=tl;i<=e;++i) p[e+tl-i]=tp[i];
	//因为是倒着插入的所以倒着复制回来
	for(int i=s;i<=sr;++i) q[i]=tq[i];
	for(int i=sl;i<=t;++i) q[t+sl-i]=tq[i];
	//同理归并
	sol(b,tr,s,sr,L,mid);
	sol(tl,e,sl,t,mid+1,R);
}
//main==========================
int main() {
	N=rd(),P=rd(),Q=rd();
	for(int i=1;i<N;++i) aE(rd(),rd());
	dfs(1);
    for(int i=1;i<=N;++i) Lx[i]=sid[i],Rx[i]=Lx[i]+sz[i]-1;
    for(int i=1;i<=P;++i) {
        int u=rd(),v=rd(),_lca=lca(u,v);h[i]=rd();
        if(Lx[u]>Lx[v]) swap(u,v);
        if(u==_lca){
			int z=upson(v,u);
			p[++m]={1,Lx[v],Rx[v],1,h[i]};
			p[++m]={Lx[z],Lx[v],Rx[v],-1,h[i]};
			if(Rx[z]<N) {
				p[++m]={Lx[v],Rx[z]+1,N,1,h[i]};
				p[++m]={Rx[v]+1,Rx[z]+1,N,-1,h[i]};
			}
        } else {
			p[++m]={Lx[u],Lx[v],Rx[v],1,h[i]};
			p[++m]={Rx[u]+1,Lx[v],Rx[v],-1,h[i]};
        }
    }
    sort(p+1,p+m+1);
    sort(h+1,h+P+1);
    h[0]=unique(h+1,h+P+1)-h-1;
    for(int i=1;i<=Q;++i) {
        int u=rd(),v=rd(),w=rd();
        if(Lx[u]>Lx[v]) swap(u,v);
        q[i]={Lx[u],Lx[v],w,i};
    }
    sort(q+1,q+Q+1);
    sol(1,m,1,Q,1,h[0]);
    for(int i=1;i<=Q;++i) printf("%d\n",ans[i]);
	return 0;
}
