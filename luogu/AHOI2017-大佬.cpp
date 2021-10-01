#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') f=-1; ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
//hash_map============================
const int _mod=1e7+7;
struct HashMap{
    struct node {
        int x,y,nxt;
    }E[_mod+100];
    int h[_mod+100],cnt;
    int hashit(int x,int y) { return (x*117ll+y)%_mod; }
    void Ins(int x,int y) {
        int t=hashit(x,y);
		E[++cnt]=node{x,y,h[t]};h[t]=cnt;
    }
    bool Qry(int x,int y) {
		int t=hashit(x,y);
        for(int i=h[t];i;i=E[i].nxt) if(E[i].x==x&&E[i].y==y) return true;
        return false;
    }
}Map;

//defs================================
int N,M,MC,D,_MX;
int a[200],w[200];
int cf[200];
//dp==================================
int f[200][200];//第i天,自信为j所能用于嘲讽的天数
//bfs=================================
struct Stat{
    int date,f,l;
    //日期，等级 ，嘲讽能力
    //这里的状态是当天还能怼的
};
vector<Stat> valid;//可行的怼法
queue<Stat> q;
void bfs() {
    q.push(Stat{1,1,0});
    while(!q.empty()) {
        Stat now=q.front();q.pop();
        if(now.date==D) break;
        q.push(Stat{now.date+1,now.f,now.l+1});
		if((ll)now.f*now.l>_MX) continue;
        if(now.l>1&&!Map.Qry(now.f*now.l,now.date+1)) {
			q.push(Stat{now.date+1,now.f*now.l,now.l});
            Map.Ins(now.f*now.l,now.date+1);
            valid.push_back(Stat{now.date+1,now.f*now.l,now.l});
            //printf("pushed %d,%d\n",now.date+1,now.f*now.l);
        }
    }
}
bool cmp(Stat x,Stat y) {
    return x.f<y.f;//||(x.f==y.f&&x.date>y.date);
}
//main================================
int main() {
	N=rd(),M=rd(),MC=rd();
	for(int i=1;i<=N;++i) a[i]=rd();
	for(int i=1;i<=N;++i) w[i]=rd();
	for(int i=1;i<=M;++i) cf[i]=rd(),_MX=max(_MX,cf[i]);
	memset(f,0xc0,sizeof f);
	f[0][MC]=0;
    for(int i=1;i<=N;++i) {
        for(int j=a[i];j<=MC;++j) {
			f[i][j-a[i]]=max(f[i][j-a[i]],f[i-1][j]+1);
			int t=min(MC,j-a[i]+w[i]);
            f[i][t]=max(f[i][t],f[i-1][j]);
			//
			D=max(D,f[i][j]);
        }
    }
    for(int i=1;i<=N;++i) for(int j=0;j<=MC;++j) D=max(D,f[i][j]);//,printf("f[%d][%d]=%d\n",i,j,f[i][j]);;
    //printf("D=%d\n",D);
    bfs();
    sort(valid.begin(),valid.end(),cmp);
    //for(int i=0;i<valid.size();++i) printf("(%d,%d)\n",valid[i].f,valid[i].date);
    #define f(i) (valid[i].f)
    #define d(i) (valid[i].date)
    for(int i=1;i<=M;++i) {
        if(cf[i]<=D) {
			puts("1");
			continue;
        }
        bool can=false;int maxv=-1e9;
		for(int j=valid.size()-1,k=0;j>=0;--j) {
			while(k<valid.size()&&f(k)+f(j)<=cf[i])
				maxv=max(maxv,f(k)-d(k)),++k;
			if(maxv+f(j)+D-d(j)>=cf[i]) {can=true;break;}
            if(f(j)<=cf[i]&&cf[i]<=D-d(j)+f(j)) {can=true;break;}
		}
		if(can) puts("1");
		else    puts("0");
    }
	return 0;
}
