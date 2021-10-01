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
    int x=0,f=1;
    char ch=getchar();
    for(; !isdigit(ch); ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch); ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
ll sub(ll a,ll b) {
    return ((a-b)%mod+mod)%mod;
}
ll qpow(ll x,ll y) {
    if(y<0) while(1);
    ll ans=1;
    for(; y; y>>=1,x=(x*x)%mod) {
        if(y&1)(ans*=x)%=mod;
    }
    return ans;
}
//main==================
int main() {
	freopen("gen.in","r",stdin);
	freopen("std.out","w",stdout);
    ll ans=1;
    N=rd();
    K=rd();
    for(int i=1; i<=N; ++i) a[i]=rd();
    sort(a+1,a+N+1);
    for(int i=1;i<(1<<N);++i){
		if(__builtin_popcount(i)!=K) continue;
        int t=0;
        for(int j=1;j<=N;++j) if(i&(1<<(j-1))) {
			++t;
			if(t!=1&&t!=K) {
                (ans*=a[j])%=mod;
			}
        }
    }
    printf("%lld\n",ans);


    return 0;
}
