#include <bits/stdc++.h>
#define db double
#define ll long long
#define maxx(a,b) ((a)>(b)?(a):(b))
using namespace std;
const int UP=1e9+1e8;
int a[50010],N;
db f[50010],g[50010];
/**
f[i] 表示把1-i-1的所有草堆爆破所需最小半径R(上一次半径为R的冲击波恰好激发了第i个草堆)
f[i] 答案具有可二分性
我们枚举R,那么可以推知f[i]自身的冲击波会影响到的最远草垛j 有 a[j]>=a[i]-R+1
那么我们只需要比对f[j]和R-1的大小就可以知道答案了
也就有式子: R-1>=a[i]-a[j] 且 f[j]<=R-1
 事实上可以直接二分点的说,这样会少一个log 
g同理

计算出f和g之后,我们枚举第一次冲击波影响到的最左点,然后可以再次二分半径,总复杂度O(nlogn^2) 
*/
double canR(db pos) {
	//printf("pos=%lf\n",pos);
	db L=1,R=max(pos-a[1],a[N]-pos),ans;
	//printf("\t%lf %lf\n",L,R);
	for(int i=1;i<=200;++i) {
		db mid=(L+R)/2;
		//printf("mid=%lf\n",mid);
		int x=lower_bound(a+1,a+N+1,pos-mid)-a,y=upper_bound(a+1,a+N+1,pos+mid)-a-1;
		if(a[x]>pos+mid||a[y]<pos-mid) L=mid;//,puts("1");
		else if(f[x]<=mid&&g[y]<=mid) R=ans=mid;//,puts("2");
		else L=mid;//,puts("3");
	}
	//printf("\tans=%lf\n",ans);
	return ans;
}
db ans=UP;
int main() {
	scanf("%d",&N);
	for(int i=1;i<=N;++i) scanf("%d",a+i);
	sort(a+1,a+N+1);
	N=unique(a+1,a+N+1)-a-1;
	//for(int i=1;i<=N;++i) printf("%d ",a[i]);puts("");
	//calc f
	f[1]=1;
	for(int i=2;i<=N;++i) {
		db L=a[i]-a[i-1],R=a[i],ans;
		for(int j=0;j<=200;++j) {
			db mid=(L+R)/2;
			int k=lower_bound(a+1,a+N+1,a[i]-mid)-a;
			if(f[k]<=mid) R=ans=mid;
			else L=mid;
		}
		f[i]=ans+1;
		//printf("f[%d]=%lf\n",i,f[i]);
	} 
	//calc_g
	g[N]=1;
	for(int i=N-1;i>=1;--i) {
		db L=a[i+1]-a[i],R=a[N]-a[i],ans;
		for(int j=0;j<=200;++j) {
			db mid=(L+R)/2;
			int k=upper_bound(a+1,a+N+1,a[i]+mid)-a-1;
			if(g[k]<=mid) R=ans=mid;
			else L=mid;
		}
		g[i]=ans+1;
		//printf("g[%d]=%lf\n",i,g[i]);
	} 
	for(int i=1;i<=N;++i) ans=min(ans,canR(a[i]));
	for(int i=2;i<=N;++i) ans=min(ans,canR((db)(a[i]+a[i-1])/2));
	printf("%.1lf\n",ans);
	return 0;
}
