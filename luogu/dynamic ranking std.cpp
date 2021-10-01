#include<bits/stdc++.h>
#define N 10005
using namespace std;
inline int lowbit(int x){return x&-x;}
int n,m,sz,totn,totx,toty,a[N],b[N<<1],ca[N],cb[N],cc[N];
int xx[N],yy[N],rt[N],size[600*N],ls[600*N],rs[600*N];
void ins(int &o,int l,int r,int x,int q,int v){
    o=++sz;size[o]=size[x]+v;ls[o]=ls[x];rs[o]=rs[x];
    if(l==r)return;int mid=(l+r)>>1;
    if(q<=mid)ins(ls[o],l,mid,ls[x],q,v);
    else ins(rs[o],mid+1,r,rs[x],q,v);
}
int query(int l,int r,int q){
    if(l==r)return l;
    int sum=0,mid=(l+r)>>1;
    for(int i=1;i<=totx;i++)sum-=size[ls[xx[i]]];
    for(int i=1;i<=toty;i++)sum+=size[ls[yy[i]]];
    if(q<=sum){
        for(int i=1;i<=totx;i++)xx[i]=ls[xx[i]];
        for(int i=1;i<=toty;i++)yy[i]=ls[yy[i]];
        return query(l,mid,q);
    }
    else{
        for(int i=1;i<=totx;i++)xx[i]=rs[xx[i]];
        for(int i=1;i<=toty;i++)yy[i]=rs[yy[i]];
        return query(mid+1,r,q-sum);
    }
}
void add(int x,int v){
    int k=lower_bound(b+1,b+totn+1,a[x])-b;
    for(int i=x;i<=n;i+=lowbit(i))ins(rt[i],1,totn,rt[i],k,v);
}
inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
int main(){char s[20];
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i]=read(),b[++totn]=a[i];
    for(int i=1;i<=m;i++){
        scanf("%s",s);ca[i]=read();cb[i]=read();
        if(s[0]=='Q')cc[i]=read();else b[++totn]=cb[i];
    }
    sort(b+1,b+totn+1);
    totn=unique(b+1,b+totn+1)-b-1;
    for(int i=1;i<=n;i++)add(i,1);
    for(int i=1;i<=m;i++){
        if(cc[i]){
            totx=toty=0;
            for(int j=ca[i]-1;j;j-=lowbit(j))xx[++totx]=rt[j];
            for(int j=cb[i];j;j-=lowbit(j))yy[++toty]=rt[j];
            printf("%d\n",b[query(1,totn,cc[i])]);
        }
        else{add(ca[i],-1);a[ca[i]]=cb[i];add(ca[i],1);}
    }
}