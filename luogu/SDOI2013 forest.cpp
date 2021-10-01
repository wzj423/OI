#include <bits/stdc++.h>
#define ll long long
using namespace std;
//tool=========================================
inline int rd(){
    int x=0;char ch=' ';int f=1;
    while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if(ch=='-')f=-1,ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
//edge========================================
struct edge{
	int ed,next;
}e[320001];
int N,M,Q,Ecnt;
int a[80001];
int fa[90001];//并查集
int son[80001];//子树大小
int head[80001];
void addEdge(int st,int ed) {
	e[++Ecnt].ed=ed,e[Ecnt].next=head[st],head[st]=Ecnt;
}
int find(int x) {
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
//data for discretization
int lisan[80001];
int lcnt;
inline int l_val(int x) {
	return lower_bound(lisan+1,lisan+lcnt+1,x)-lisan;
}
//seg_tree=============================================
struct node {
	int sum,l,r;
}T[80001*600];
int root[80001];
int Tcnt;
void insert(int &now,int x,int L,int R) {
	T[++Tcnt]=T[now];
	now=Tcnt;
	++T[now].sum;
	if(L==R)	return;
	int mid=(L+R)>>1;
	if(x<=mid)	insert(T[now].l,x,L,mid);
	else		insert(T[now].r,x,mid+1,R);
}
int query(int x,int y,int pre1,int pre2,int k,int L,int R) {//returns the real value
	if(L==R)	return lisan[L];
	int lsize=T[ T[x].l ].sum+T[ T[y].l ].sum
		-T[ T[pre1].l ].sum-T[ T[pre2].l ].sum;
	int mid=(L+R)>>1;
	if(k<=lsize)	return query(T[x].l,T[y].l,T[pre1].l,T[pre2].l,k,L,mid);
	else	return query(T[x].r,T[y].r,T[pre1].r,T[pre2].r,k-lsize,mid+1,R);
}
//data for lca================================
int st[80001][17];
int dep[80001];
int vis[80001];
void dfs(int x,int father,int rt) {
	st[x][0]=father;
	for(int k=1;k<=16;++k)
		st[x][k]=st[ st[x][k-1] ][k-1];
	son[rt]++;
	dep[x]=dep[father]+1;
	fa[x]=father;///子树根变了，重设并查集
	vis[x]=1;
	root[x]=root[father];
	insert(root[x],l_val(a[x]),1,lcnt);
	for(int i=head[x];i;i=e[i].next) {
        int u=e[i].ed;
        if(u==father)   continue;
        dfs(u,x,rt);
	}
}
int getlca(int x,int y) {
    if(x==y)    return x;
    if(dep[x]>dep[y])   swap(x,y);
    for(int k=16;k>=0;--k) {
        if(dep[st[y][k]]>=dep[x])
            y=st[y][k];
    }
    if(x==y)    return x;
    for(int k=16;k>=0;--k) {
        if(st[x][k]!=st[y][k])
            x=st[x][k],y=st[y][k];
    }
    return st[x][0];
}
//main========================================
int main() {
    rd();
    Ecnt=Tcnt=0;
    N=rd(),M=rd(),Q=rd();
    for(int i=1;i<=N;++i)
        a[i]=lisan[i]=rd(),fa[i]=i;
    sort(lisan+1,lisan+N+1);
    lcnt=unique(lisan+1,lisan+N+1)-lisan-1;
    for(int i=1;i<=M;++i) {
        int x=rd(),y=rd();
        addEdge(x,y),addEdge(y,x);
    }
    for(int i=1;i<=N;++i) {
        if(!vis[i]) {
            dfs(i,0,i);
            fa[i]=i;
        }
    }
    int lastans=0;
    for(int i=1;i<=Q;++i) {
        char opt[10];
        int x,y,k;
        scanf("%s",opt);
        x=rd()^lastans;
        y=rd()^lastans;
        if(opt[0]=='Q') {
            k=rd()^lastans;
            int lca=getlca(x,y);
            lastans=query(root[x],root[y],root[lca],root[st[lca][0]],k,1,lcnt);
            printf("%d\n",lastans);
        } else {
            addEdge(x,y);
            addEdge(y,x);
            int u=find(x),v=find(y);
            if(son[u]<son[v]) {
                swap(u,v);
                swap(x,y);
            }
            dfs(y,x,u);
        }
    }
	return 0;
}
