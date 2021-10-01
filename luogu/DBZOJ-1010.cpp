#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long LL;
const int MAXN=50010;
int N,L;
db sum[MAXN],dp[MAXN];
int head,tail,Q[MAXN];
inline db a(int i) {return sum[i]+i; }
inline db b(int i) {return a(i)+L+1; }
inline db X(int i) {return b(i); }
inline db Y(int i) {return dp[i]+b(i)*b(i);  }
inline db slope(int i,int j) { return (Y(i)-Y(j))/(X(i)-X(j)); }
int main()
{
    scanf("%d%d",&N,&L);
    for(int i=1;i<=N;++i)
    {
        scanf("%lf",sum+i);
        sum[i]+=sum[i-1];
    }
    head=tail=1;
    for(int i=1;i<=N;++i)
    {
        while(head<tail && slope(Q[head],Q[head+1]) < 2*a(i) ) ++head;
        dp[i]=dp[ Q[head] ]+(a(i)-b( Q[head] )) * (a(i)-b( Q[head] ));
        while(head<tail && slope(i,Q[tail-1]) < slope(Q[tail-1],Q[tail]) ) --tail;
        Q[++tail]=i;
    }
    printf("%lld\n",(LL)dp[N]);
    return 0;
}