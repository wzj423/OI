/**
蚯蚓
Luogu P2827
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
typedef long long LL;
int N,M,Q,U,V,T;
double P;
priority_queue <int > Que;
int totAddMark;//每次切割的累加值
// code

void init()
{
    scanf("%d%d%d%d%d%d",&N,&M,&Q,&U,&V,&T);
    P=(U*1.0)/V;
    int x;
    for(int i=1; i<=N; ++i)
    {
        scanf("%d",&x);
        Que.push(x);
    }

    //cout<<P<<endl;
}
void cut(int oriLen)
{
    static int cutCnt=0;
    cutCnt++;
    if(cutCnt%T==0)
        cout<<oriLen<<" ";
    int x1,x2;
    x1=P*oriLen;
    x2=oriLen-x1;
    totAddMark+=Q;
    x1-=totAddMark;
    x2-=totAddMark;

    Que.push(x1);
    Que.push(x2);
}
void work()
{
    for(int i=1; i<=M; ++i)
    {
        int t=Que.top();
        Que.pop();
        cut(t+totAddMark);
    }
    cout<<endl;
    int up=Que.size();
    for(int i=1; i<=up; ++i)
    {
        int t=Que.top();
        Que.pop();
        if(i%T==0)
            cout<<t+totAddMark<<" ";
    }
    cout<<endl;
}
int main()
{
    init();
    work();
    return 0;
}
/*
#include <cstdio>
#include <algorithm>
#define AA(x) (a[x]+(i-1)*q)
#define BB(x) (b[x]+(i-1)*q)
#define CC(x) (c[x]+(i-1)*q)
#define Max(x,y,z) max(x,max(y,z))
using namespace std;
long long n,m,q,u,v,t,k,k1,k2;
long long a[100005],b[7000005],c[7000005],A=1,B=1,C=1,rb,rc;
bool cmp(int x,int y)
{
    return x>y;
}

long long Getk(int i)
{
    long long x1,x2,x3,xx;
    x1=x2=x3=-1;
    if(A<=n) x1=AA(A);
    if(B<=rb) x2=BB(B);
    if(C<=rc) x3=CC(C);
    xx=max(x1,max(x2,x3));
    if(xx==x1)
    {
        A++;
        return x1;
    }
    if(xx==x2)
    {
        B++;
        return x2;
    }
    else
    {
        C++;
        return x3;
    }
}

int main()
{
    scanf("%lld%lld%lld%lld%lld%lld",&n,&m,&q,&u,&v,&t);
    for(int i=1; i<=n; i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1,cmp);
    for(int i=1; i<=m; i++)
    {
        k=Getk(i);
        if(i%t==0) printf("%lld ",k);
        k1=k*u/v, k2=min(k1,k-k1), k1=k-k2;
        b[++rb]=k1-i*q;
        c[++rc]=k2-i*q;
    }
    printf("\n");
    for(int i=1; i<=n+m; i++)
    {
        k=Getk(m+1);
        if(i%t==0) printf("%lld ",k);
    }
    return 0;
}
*/



