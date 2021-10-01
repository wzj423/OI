#include <bits/stdc++.h>
#define ll long long
#define lc (x<<1)
#define rc (x<<1|1)
using namespace std;
int N,M;const int MAXN=100100;
ll a[MAXN],f[MAXN];
/*
	首先我们有O(N^2)的转移方程
	f[i]表示到第i本书位置单独成为多层的最小高度
	则有:
        f[i]=min(f[j]+max(a[j+1 to i]))
        有:sum(j+1,i)<=M
    sum限制用单调栈得出,易知对于i,最小的j单调不减
    现在考虑处理min部分的优化:
        对于每一个a[i],添加进来时会影响之前的连续一段max,
        这一段我们也可以用单调栈预处理
        那么线段树优化就是很显然的
    考虑线段树上维护两个值a,b,单点a赋值,区间b赋值,以及区间a+b最小值
		就可以做了
	具体线段树实现用以下标记:
        vf->f的最小值 vt->总得最小值 ts->区间赋值的lazy_tag
*/
int s[MAXN],top,q[MAXN],hh,tt;
int mxin[MAXN],slim[MAXN];
ll vf[MAXN*8],vt[MAXN*8],ts[MAXN*8];
void pushdown(int x) {
	if(!ts[x]) return;
	vt[x]=vf[x]+ts[x];//情况1的update
    ts[lc]=ts[rc]=ts[x];ts[x]=0;
}
void modify_f(int pos,ll val,int L=0,int R=N,int x=1) {
	pushdown(x);
    if(L==R) {
		vt[x]=vt[x]-vf[x]+val;
        vf[x]=val;
    //    printf("[%d,%d] vf[%d]=%lld\n",L,R,x,vf[x]);
        return;
    }
    int mid=(L+R)/2;
    if(pos<=mid) modify_f(pos,val,L,mid,lc);
    else		modify_f(pos,val,mid+1,R,rc);
    pushdown(lc),pushdown(rc);
    vf[x]=min(vf[lc],vf[rc]);
    vt[x]=min(vt[lc],vt[rc]);
    //printf("[%d,%d] vt=%lld vf=%lld\n",L,R,vt[x],vf[x]);
}
void set_a(int B,int E,ll val,int L=0,int R=N,int x=1) {
    pushdown(x);
    if(E<L || B>R || B>E) return ;
    if(B<=L && R<=E) {
        ts[x]=val;
        vt[x]=vf[x]+val;
    //    printf("in set: [%d,%d] vt[%d]=%lld\n",L,R,x,vt[x]);
        return ;
    }
    int mid=(L+R)>>1;
    set_a(B,E,val,L,mid,lc),set_a(B,E,val,mid+1,R,rc);
    pushdown(lc),pushdown(rc);
    vf[x]=min(vf[lc],vf[rc]);
    vt[x]=min(vt[lc],vt[rc]);
}
ll qry(int B,int E,int L=0,int R=N,int x=1) {
    pushdown(x);
    if(E<L || B>R || B>E) return (ll)(1e17);
    if(B<=L && R<=E) {
	//		printf("in[%d,%d] x=%d ret=%lld vf=%lld\n",L,R,x,vt[x],vf[x]);
        return vt[x];
    }
    int mid=(L+R)>>1;
	ll ret=min(qry(B,E,L,mid,lc),qry(B,E,mid+1,R,rc));
	//		printf("in[%d,%d] x=%d ret=%lld\n",L,R,x,ret);
	return ret;
}
int main() {
	freopen("gen.in","r",stdin);
	freopen("my.out","w",stdout);
	memset(vf,0x3f,sizeof vf);memset(vt,0x3f,sizeof vt);
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i) scanf("%lld",a+i);
	for(int i=1;i<=N;++i) {
        while(top&&a[s[top]]<a[i]) --top;
        mxin[i]=s[top]+1;
        s[++top]=i;
        //if(mxin[i]==1) mxin[i]=0;
        //printf("%d ",mxin[i]);
	}
	//puts("");
	ll t=0;
	for(int i=1;i<=N;++i) {
        q[++tt]=i;t+=a[i];
        while(hh<tt && t>M ) ++hh,t-=a[q[hh]];
        slim[i]=q[hh+1];
        //printf("%d ",slim[i]);
	}
	//puts("");
	modify_f(0,0);
	for(int i=1;i<=N;++i) {
		set_a(mxin[i]-1,i,a[i]);
		//printf("set_a[%d,%d] as %lld\n",mxin[i],i,a[i]);
		f[i]=qry(slim[i]-1,i-1);
		//printf("query in[%d,%d]\n",slim[i]-1,i-1);
        modify_f(i,f[i]);

        //printf("f[%d]=%lld\n",i,f[i]);
	}
	printf("%lld\n",f[N]);
	return 0;
}
