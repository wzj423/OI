#include <bits/stdc++.h>
#define ll long long
using namespace std;
//defs==================
const int MAXN=1010,mod=1e9+7;
ll T,N,K;
ll a[MAXN],s[MAXN],pp[MAXN];
ll C[MAXN][MAXN];
//tool======================
inline int rd() {
	int x=0,f=1; char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
ll sub(ll a,ll b) {
	return ((a-b)%mod+mod)%mod;
}
ll qpow(ll x,ll y) {
	if(y<0) while(1);
    ll ans=1;
    for(;y;y>>=1,x=(x*x)%mod) {
        if(y&1) (ans*=x)%=mod;
    }
    return ans;
}
//main==================
int main() {
	freopen("gen.in","r",stdin);
	freopen("my.out","w",stdout);
	C[0][0]=1;
	for(int i=1;i<=1005;++i)
		for(int j=0;j<=i;++j)
			if(j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
			else C[i][j]=C[i-1][j];
	T=1;
    while(T--) {
		ll ans=1;
		N=rd();K=rd();
		for(int i=1;i<=N;++i) a[i]=rd();
		sort(a+1,a+N+1);
//        for(int i=1;i<=K;++i) s[i]=C[K-1][i]*C[K-1][K-i-1]%mod;
//        for(int i=1;i<=N;++i) pp[i]=(pp[i-1]+s[i])%mod;
        for(int i=2;i<N;++i) {
            ll t=C[N-1][K-1];
            if(i-1>=K-1) t=sub(t,C[i-1][K-1]);
            if(N-i>=K-1) t=sub(t,C[N-i][K-1]);
            //printf("i=%lld a[i]=%lld t=%lld\n",i,a[i],t);
			ans*=qpow(a[i],t);
			ans%=mod;
        }
        printf("%lld\n",ans);
    }

	return 0;
}
