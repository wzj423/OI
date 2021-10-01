#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b) {
    return a<b?a=b,1:0;
}
template<class T>inline bool cmin(T&a,const T&b) {
    return a>b?a=b,1:0;
}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc() {
    return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;
}
template<class T>inline void sd(T&x) {
    char c;
    T y=1;
    while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;
    x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;
    x*=y;
}
char sr[1<<21],z[20];
int C=-1,Z;
inline void Ot() {
    fwrite(sr,1,C+1,stdout),C=-1;
}
template<class T>inline void we(T x) {
    if(C>1<<20)Ot();
    if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);
    sr[++C]='\n';
}
const int N=2e5+5,inf=1e9;
typedef int arr[N];
struct eg {
    int nx,to;
} e[N];
struct Line {
    int x,L,R,w,val;
    inline bool operator<(const Line b)const {
        return x<b.x;
    }
} p[N],tp[N];
struct qry {
    int x,y,k,id;
    inline bool operator<(const qry b)const {
        return x<b.x;
    }
} q[N],tq[N];
int n,m,Q,dft;
arr c,h,fa,fi,sz,Lx,Rx,dep,son,top,ans;
void dfs(int u) {
    dep[u]=dep[fa[u]]+(sz[u]=1);
    go(u)if(v^fa[u]) {
        fa[v]=u,dfs(v),sz[u]+=sz[v];
        if(sz[v]>sz[son[u]])son[u]=v;
    }
}
void dfs(int u,int t) {
    Lx[u]=++dft;
    top[u]=t;
    if(son[u])dfs(son[u],t);
    go(u)if(v^fa[u]&&v^son[u])dfs(v,v);
    Rx[u]=dft;
}
inline int Go(int u,int p) {
    while(top[u]^top[p]) {
        if(fa[top[u]]==p)return top[u];
        u=fa[top[u]];
    }
    return top[u]==u?u:son[p];
}
inline void mdy(int i,int w) {
    for(; i<=n; i+=i&-i)c[i]+=w;
}
inline int qry(int i) {
    int w=0;
    for(; i; i-=i&-i)w+=c[i];
    return w;
}
inline void mdy(int L,int R,int w) {
    mdy(L,w),mdy(R+1,-w);
}
void sol(int b,int e,int s,int t,int L,int R) {
    if(b>e||s>t)return;
    if(L==R) {
        fp(i,s,t)ans[q[i].id]=h[L];
        return;
    }
    int mid=(L+R)>>1,tl=b,tr=e,sl=s,sr=t,j=b,sp;
    fp(i,s,t) {
        for(; j<=e&&p[j].x<=q[i].x; ++j)
            if(p[j].val>h[mid])tp[tr--]=p[j];
            else mdy(p[j].L,p[j].R,p[j].w),tp[tl++]=p[j];
        q[i].k>(sp=qry(q[i].y))?q[i].k-=sp,tq[sr--]=q[i]:tq[sl++]=q[i];
    }
    for(; j<=e; ++j)if(p[j].val>h[mid])tp[tr--]=p[j];
        else mdy(p[j].L,p[j].R,p[j].w),tp[tl++]=p[j];
    fp(i,b,tr) mdy(tp[i].L,tp[i].R,-tp[i].w);
    fp(i,b,tr) p[i]=tp[i];
    fp(i,tl,e) p[e+tl-i]=tp[i];
    fp(i,s,sr) q[i]=tq[i];
    fp(i,sl,t) q[t+sl-i]=tq[i];
    sol(b,tr,s,sr,L,mid);
    sol(tl,e,sl,t,mid+1,R);
}
inline void add(int u,int v) {
    static int ce=0;
    e[++ce]= {fi[u],v},fi[u]=ce;
}
int main() {
#ifndef ONLINE_JUDGE
    file("s");
#endif
    int u,v,w;
    sd(n),sd(w),sd(Q);
    fp(i,2,n)sd(u),sd(v),add(u,v),add(v,u);
    dfs(1),dfs(1,1);
    fp(i,1,w) {
        sd(u),sd(v),sd(h[i]);
        if(Lx[u]>Lx[v])swap(u,v);
        if(Lx[u]<=Lx[v]&&Rx[v]<=Rx[u]) {
            int z=Go(v,u);
            p[++m]= {1,Lx[v],Rx[v],1,h[i]};
            p[++m]= {Lx[z],Lx[v],Rx[v],-1,h[i]};
            if(Rx[z]<n)p[++m]= {Lx[v],Rx[z]+1,n,1,h[i]},
                        p[++m]= {Rx[v]+1,Rx[z]+1,n,-1,h[i]};
        } else p[++m]= {Lx[u],Lx[v],Rx[v],1,h[i]},
                p[++m]= {Rx[u]+1,Lx[v],Rx[v],-1,h[i]};
    }
    sort(p+1,p+m+1);
    sort(h+1,h+w+1);
    h[0]=unique(h+1,h+w+1)-h-1;
    fp(i,1,Q) {
        sd(u),sd(v),sd(w);
        if(Lx[u]>Lx[v])swap(u,v);
        q[i]= {Lx[u],Lx[v],w,i};
    }
    sort(q+1,q+Q+1);
    sol(1,m,1,Q,1,h[0]);
    fp(i,1,Q)we(ans[i]);
    return Ot(),0;
}
