#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e9+7;
int N,M,K;
ll f[1010000];
ll ans,tp;
ll qpow(ll a,ll b) {
	ll ans=1;
	for(;b;b>>=1,a=(a*a)%mod) if(b&1) ans=(ans*a)%mod;
	return ans;
}
inline void mdv(ll &a,ll b) {
	a=((a-b)%mod+mod)%mod;
}
int main() {
	scanf("%d%d%d",&N,&M,&K);
	ans=qpow(M,N);
	if(K==1) {
		printf("%lld\n",ans);
		return 0;
	}
	f[0]=1;
	for(int i=1;i<=N;++i) {
		f[i]=f[i-1]*M%mod;
		if(i==K) {
			mdv(f[i],f[i-K]*M%mod);
		}else if(i>=K+1) {
			mdv(f[i],f[i-K]*(M-1)%mod);
		}
		//printf("f[%d]=%lld\n",i,f[i]);
	}
	mdv(ans,f[N]);
	printf("%lld\n",ans);
	return 0;
} 
