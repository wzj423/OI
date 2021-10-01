#include <bits/stdc++.h>
#define R register int
#define ll long long
using namespace std;
/**
50 pts:
dp[i][j]=前i个切j次
dp[i][j]=dp[k (k<i) ][j-1]+(sum[i]-sum[k])*sum[k]

try to get 100 pts
dp[i][j]=dp[k (k<i) ][j-1]+sum[i]*sum[k]-sum[k]*sum[k]
以j滚动数组
则化归方程式为
dp[i]=dp[k (k<i) ]+sum[i]*sum[k]-sum[k]*sum[k]
如有k<l<i比k更优，则有：
dp[l]+sum[i]*sum[l]-sum[l]*sum[l] > dp[k]+sum[i]*sum[k]-sum[k]*sum[k]
sum[i]*(sum[l]-sum[k]) > dp[k]-dp[l]-sum[k]*sum[k]+sum[l]*sum[l]
sum[i] > dp[k]-dp[l]-sum[k]*sum[k]+sum[l]*sum[l] / (sum[l]-sum[k])
令每个状态代表一点 (sum[x],sum[x]^2-dp[x])
则有，sum[i] > slope(l,k)
*/
///tool==================================
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) { if(ch=='-') f=-1;ch=getchar(); }
    while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
    return x*f;
}
//defs====================================
const int MAXN=1e5+10,INF=0x3f3f3f3f;
int N,K;
ll a[MAXN],sum[MAXN];
ll dp[MAXN][2];
int cur;
int q[MAXN*4],l,r;
int to[210][MAXN];//存储方案
//code=========================================
double slope(int x,int y) {
    if(sum[x]==sum[y])  return -INF;
    return ( (sum[x]*sum[x]-dp[x][cur^1])-(sum[y]*sum[y]-dp[y][cur^1]) )*1.0/(sum[x]-sum[y]);
}
//main=======================================
int main() {
    N=rd(),K=rd();
    for(R i=1;i<=N;++i)
        a[i]=rd(),sum[i]=a[i]+sum[i-1];
    for(R j=1;j<=K;++j) {
        l=r=0;cur^=1;
        for(R i=1;i<=N;++i ) {
            while(l<r && slope(q[l],q[l+1]) <= sum[i]) ++l;
            dp[i][cur]= dp[ q[l] ][cur^1]+(sum[i]-sum[ q[l] ])*sum[ q[l] ];
            to[j][i]=q[l];
            while(l<r && slope(q[r-1],q[r]) >= slope(q[r],i)) --r;
            q[++r]=i;
        }
    }
    printf("%lld\n",dp[N][cur]);
    int i=N;
    for(R j=K;j>=1;--j) {
        i=to[j][i];
        printf("%d ",i);
    }
    return 0;
}
