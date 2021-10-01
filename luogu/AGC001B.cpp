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
ll N,X;
ll ans;
void solve(ll a,ll b) {
	if(a<b) swap(a,b);
	if(a%b==0) {
		ans+=a/b*b*2-b;
		return;
	}
	ans+=a/b*b*2;
	solve(b,a%b);
}
//main=============================
int main() {
	scanf("%lld%lld",&N,&X);
	ans=N;
	solve(N-X,X);
	cout<<ans<<endl;
	return 0;
}

