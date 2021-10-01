#include <bits/stdc++.h>

using namespace std;
inline int rd() {
	int x=0,f=1; char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
int N,Q,Block;
const int MAXN=1e6+10;
struct ele{
	int vv,id;
	bool operator<(int x) {
		return vv<x;
	}
}a[MAXN];
bool cmp(ele x,ele y) {
	return x.vv<y.vv;
}
struct part {
    int L,R,len,tag;
}B[2000];
int cnt=0;
//modules======================
void build_kuai() {
    while(1) {
		++cnt;
        B[cnt].L=B[cnt-1].R+1;
        B[cnt].R=min(B[cnt].L+Block-1,N);
		B[cnt].len=B[cnt].R-B[cnt].L+1;
        sort(a+B[cnt].L,a+B[cnt].R+1,cmp);
        if(N==B[cnt].R) break;
    }
}
int QryComplete(part &x,int num) {
    num-=x.tag;
    ele *l=lower_bound(a+x.L,a+x.R+1,num);
	return a+x.R-l+1;
}
void ModiComplete(part &x,int num) {
	x.tag+=num;
}
int QryPart(part &x,int num,int L,int R) {
	if(L>R) return 0;
    int ret=0;
    for(int i=x.L;i<=x.R;++i) if(a[i].id<=R&&a[i].id>=L)ret+=(a[i].vv+x.tag>=num);
	return ret;
}
void ModiPart(part &x,int num,int L,int R) {
	if(L>R) return;
    for(int i=x.L;i<=x.R;++i) {
        a[i].vv+=x.tag;
        if(L<=a[i].id&&a[i].id<=R) a[i].vv+=num;
    }
    x.tag=0;
    sort(a+x.L,a+x.R+1,cmp);
}
char _opt() {
    static char _t[4];
    scanf("%s",_t);
    return _t[0];
}
//main=========================
int main() {
	N=rd(),Q=rd();Block=sqrt(N);
	for(int i=1;i<=N;++i) {
		a[i].vv=rd();
		a[i].id=i;
	}
	build_kuai();
    while(Q--) {
		int flag=_opt()=='M';
		int L=rd(),R=rd(),x=rd();
		if(flag) {
            for(int i=1;i<=cnt;++i) {
                if(B[i].L>=L&&B[i].R<=R) ModiComplete(B[i],x);
                else ModiPart(B[i],x,max(B[i].L,L),min(B[i].R,R));
            }
		} else {
			int ans=0;
            for(int i=1;i<=cnt;++i) {
                if(B[i].L>=L&&B[i].R<=R) ans+=QryComplete(B[i],x);
                else ans+=QryPart(B[i],x,max(B[i].L,L),min(B[i].R,R));
            }
			printf("%d\n",ans);
		}
    }
	return 0;
}
