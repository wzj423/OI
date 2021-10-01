#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
#define db double
#define LL long long
LL N,x[MAXN],p[MAXN],c[MAXN];
LL sum[MAXN],g[MAXN];
LL f[MAXN];
db q[MAXN];
int head,tail;
db X(int i) {return (1.0*sum[i]);}
db Y(int i) {return (1.0*( f[i]+g[i] ));}
#define slope(i,j) ( (Y(i)-Y(j)) / (X(i)-X(j)) )
//main
int main()
{
    scanf("%lld",&N);
    for(int i=1;i<=N;++i)
        scanf("%lld%lld%lld",x+i,p+i,c+i);
    for(int i=1;i<=N;++i)
    {
        sum[i]=sum[i-1]+p[i];
        g[i]=g[i-1]+x[i]*p[i];
    }
    for(int i=1;i<=N;++i)
    {
        while(head<tail && slope(q[head],q[head+1])<x[i]) ++head;
        int t=q[head];
        f[i]=f[t]-g[i]+g[t]+(sum[i]-sum[t])*x[i]+c[i];
        while(head<tail && slope(q[tail-1],q[tail]) > slope(q[tail],i) )--tail;
        q[++tail]=i;
    }
    printf("%lld",f[N]);
    return 0;
}