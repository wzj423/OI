/**
黑匣子
Luogu P1801
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
long long M,N;
long long q[4001000];
long long addNum[2001000];
long long queryNum[2001000];
long long qcnt;
long long queryId;
priority_queue <long long> qBig;
priority_queue <long long,vector<long long>,greater<long long> > qSmall;
/// code
/*void push(long long x)
{
    q[++qcnt]=x;
    long long id=qcnt;
    while(id>1)
    {
        if(q[id]<q[id/2])
        {
            swap(q[id],q[id/2]);
            id/=2;
        }
        else
            break;
    }
}
void pop()
{
    q[1]=q[qcnt];
    qcnt--;
    long long id=1;
    long long tar;
    while(id*2<=qcnt)
    {
        tar=id*2;
        if(tar+1<=qcnt&&q[tar]>q[tar+1])
            ++tar;
        if(q[tar]<q[id])
            swap(q[tar],q[id]);
        else
            break;
    }
}*/
void init()
{
    scanf("%lld%lld",&M,&N);
    for(long long i=1; i<=M; ++i)
        scanf("%lld",&addNum[i]);
    for(long long j=1; j<=N; ++j)
    {
        long long x;
        scanf("%lld",&x);
        ++queryNum[x];
    }

}
void work()
{
    for(long long i=1;i<=M;++i)
    {
        qBig.push(addNum[i]);
        for(long long j=1;j<=queryNum[i];++j)
        {
            ++queryId;
            while(qBig.size()<queryId)//! 如果小了
            {
                long long x=qSmall.top();
                qSmall.pop();
                qBig.push(x);
            }
            while(qBig.size()>queryId)
            {
                long long x=qBig.top();
                qBig.pop();
                qSmall.push(x);
            }
            printf("%lld\n",qBig.top());

        }
    }
}
int main()
{
    /*freopen("blackbox.in","r+",stdin);
    freopen("blackbox.out","w+",stdout);*/
    init();
    work();
    return 0;
}
