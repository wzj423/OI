#include <bits/stdc++.h>

using namespace std;
//tool====================
inline int rd() {
	int x=0,f=1; char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
//defs====================
const int MAXN=6e5;
int N,M;
int a[MAXN],bl[MAXN];
//SA======================
int Len,Mset;
int sa[MAXN],rak[MAXN],tp[MAXN],tax[MAXN],height[MAXN];
void Qsort() {
    for(int i=0;i<=Mset;++i) tax[i]=0;
	for(int i=1;i<=Len;++i) tax[rak[i]]++;
	for(int i=1;i<=Mset;++i) tax[i]+=tax[i-1];
	for(int i=Len;i;--i) sa[ tax[rak[tp[i]]]-- ]=tp[i];
}
void Ssort() {
	Mset=5e5;
    for(int i=1;i<=Len;++i) {
        rak[i]=a[i];
        tp[i]=i;
    }
	Qsort();
    for(int w=1,p=0; p<Len; Mset=p,w<<=1) {
		p=0;
        for(int i=w;i>=1;--i) tp[++p]=Len-w+i;
		for(int i=1;i<=Len;++i) if(sa[i]>w) tp[++p]=sa[i]-w;
		Qsort();
		swap(rak,tp);
		rak[sa[1]]=1;
        p=1;
        for(int i=2;i<=Len;++i)
			if(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+w]==tp[sa[i-1]+w])
				rak[sa[i]]=p;
			else rak[sa[i]]=++p;
    }
    for(int i=1;i<=Len;++i) rak[sa[i]]=i;
    int i,j,k=0;
    for(i=1;i<=Len;height[rak[i++]]=k)
        for(k=k?k-1:k,j=sa[rak[i]-1];a[i+k]==a[j+k];++k);
}
int st[MAXN][20];
void build_st() {
	for(int i=1;i<=Len;++i) st[i][0]=height[i];
	for(int j=1;j<=18;++j)
		for(int i=1;i+(1<<j)-1<=Len;++i)
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
//string==================
void ins_str(int l,int _ch,int belong=true) {
    for(int i=1;i<=l;++i) a[++Len]=rd(),bl[Len]=(_ch>>1)*belong;
    a[++Len]=2e5+_ch;
}
//Mo's algorithm==========
int Block,rid[MAXN];
struct qq{
	int L,R,len;//串上
    int B,E,ans;//height上
    int id;
}Q[MAXN];
bool cmp(qq x,qq y) {
    if(bl[x.B]!=bl[y.B]) return bl[x.B]<bl[y.B];
    if(bl[x.B]&1) return x.E<y.E;
    else	return x.E>y.E;
}
void deal_qry(qq &x) {
    int t=rak[x.L];
	for(int j=18;j>=0;--j) if(st[t+1][j]>=x.len) t+=(1<<j);
	x.E=t;
    for(int j=18;j>=0;--j) if(t-(1<<j)+1>=1&&st[t-(1<<j)+1][j]>=x.len) t-=(1<<j);
    x.B=t;
}
int cnt[MAXN],tot;
int vis[MAXN];
int ans1[MAXN];
int ans2[MAXN];
void add(int x,int qid) {
	if(!x) return;
    if(++cnt[x]==1) {
		++tot;
        ans2[x]+=(M-qid+1);
    }

}
void del(int x,int qid) {
	if(!x) return;
	if(--cnt[x]==0) {
		--tot;
		ans2[x]-=(M-qid+1);
	}
}
//main====================
int main() {
	N=rd();M=rd();
    for(int i=1;i<=N;++i) ins_str(rd(),i<<1),ins_str(rd(),i<<1|1);
    for(int i=1;i<=M;++i) Q[i].id=i,Q[i].L=Len+1,Q[i].len=rd(),Q[i].R=Len+Q[i].len,ins_str(Q[i].len,N*2+i+1,0);

    Ssort();
    build_st();
	for(int i=1;i<=M;++i) deal_qry(Q[i]);
    Block=sqrt(Len);
    for(int i=1;i<=Len;++i) rid[i]=(i-1)/Block+1;
	sort(Q+1,Q+M+1,cmp);

    //Modui
    int B=Q[1].B,E=Q[1].E;
    for(int i=B;i<=E;++i) add(bl[sa[i]],1);
    ans1[Q[1].id]=tot;
    for(int i=2;i<=M;++i) {
		while(B<Q[i].B) del(bl[sa[B++]],i);
		while(B>Q[i].B) add(bl[sa[--B]],i);
		while(E>Q[i].E) del(bl[sa[E--]],i);
		while(E<Q[i].E) add(bl[sa[++E]],i);
		ans1[Q[i].id]=tot;
    }
	for(int i=1;i<=M;++i) printf("%d\n",ans1[i]);
	for(int i=1;i<=N;++i) printf("%d ",ans2[i]);
	puts("");
	return 0;
}
