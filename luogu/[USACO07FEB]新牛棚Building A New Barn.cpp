#include <bits/stdc++.h>
typedef long long ll;
typedef double db;
#define mk make_pair
#define pa pair<int,int>
using namespace std;

inline int rd() {
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	return x*f;
}
struct pos{
	int x,y;
}a[10010];
int N; 
bool cmp_x(pos x,pos y) {
	return x.x<y.x;
}
bool cmp_y(pos x,pos y) {
	return x.y<y.y;
}
ll totdis(int x,int y) {
	ll ans=0;
	for(int i=1;i<=N;++i) ans+=abs(x-a[i].x)+abs(y-a[i].y);
	return ans; 
}
const int _x[]={0,0,1,-1};
const int _y[]={1,-1,0,0};
//main=============================
int main() {
	scanf("%d",&N);
	for(int i=1;i<=N;++i) scanf("%d%d",&a[i].x,&a[i].y);
	if(N%2) {
		sort(a+1,a+N+1,cmp_x);
		int xx=a[N/2+1].x;
		sort(a+1,a+N+1,cmp_y);
		int yy=a[N/2+1].y;
		int ans=0,minv=1e9;
		for(int i=0;i<4;++i) {
			int t=totdis(xx+_x[i],yy+_y[i]);
			if(minv>t) {
				minv=t;
				ans=1;
			} else if(minv==t) {
				++ans;
			}
		}
		printf("%d %d\n",minv,ans);
	} else {
		sort(a+1,a+N+1,cmp_x);
		int x1=a[N/2].x,x2=a[N/2+1].x;
		sort(a+1,a+N+1,cmp_y);
		int y1=a[N/2].y,y2=a[N/2+1].y;
		ll ans=(x2-x1+1)*(y2-y1+1);
		for(int i=1;i<=N;++i) if(x1<=a[i].x&&a[i].x<=x2&&y1<=a[i].y&&a[i].y<=y2) --ans;
		printf("%lld %lld\n",totdis(x1,y1),ans);
	}
	return 0;
}

