/*
Accepted!
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
const int MAXN=100010;
const int INF=0x3f3f3f3f;
typedef  long long  LL;

LL H[MAXN];
LL X[MAXN];
LL Q[MAXN];
LL N,M;

map<LL,LL> hei;
typedef map<LL,LL>::iterator Iter;
typedef map<LL,LL>::reverse_iterator RIter;
LL a[MAXN];//目的地
LL b[MAXN];//

LL aNext[MAXN];
LL bNext[MAXN];

LL F[MAXN][23];//两天一次,2^j次 目的地
LL adis[MAXN][23];//距离
LL bdis[MAXN][23];
// code
void init()
{
    scanf("%lld",&N);
    for(LL i=1; i<=N; ++i)
        scanf("%lld",&H[i]);
    scanf("%lld",&X[0]);
    scanf("%lld",&M);
    for(LL i=1; i<=M; ++i)
        scanf("%lld%lld",&Q[i],&X[i]);
}
bool cmp(pair<LL,LL> a,pair<LL,LL> b)
{
    if(abs(a.first)!=abs(b.first))
        return abs(a.first)<abs(b.first);//差小在前
    return a.first<b.first;//负号在前
}
void calc_next()
{
    vector<pair<LL,LL> > t;
    for(LL i=N; i>=1; --i)
    {
        t.clear();
        RIter tmp1;
        Iter tmp2;

        hei[H[i]]=i;
        tmp2=hei.find(H[i]);//tmp2 向后 tmp1向前
        ++tmp2;
        if(tmp2!=hei.end())
        {
            t.push_back(*tmp2);
            ++tmp2;
            if(tmp2!=hei.end())
                t.push_back(*tmp2);
            --tmp2;
        }
        --tmp2;
        if(tmp2!=hei.begin())
        {
            --tmp2;
            t.push_back(*tmp2);
            if(tmp2!=hei.begin())
            {
                --tmp2;
                t.push_back(*tmp2);
                ++tmp2;
            }
            ++tmp2;
        }
        //开始排序
        for(LL j=0; j<t.size(); ++j)
            t[j].first-=H[i];

        sort(t.begin(),t.end(),cmp);

        if(t.size()>0)
        {
            b[i]=t[0].second;
            bNext[i]=abs(t[0].first);
            if(t.size()>1)
            {
                a[i]=t[1].second;
                aNext[i]=abs(t[1].first);
            }
        }
    }
}
void calc_double()//倍增
{
    for(LL i=1;i<=N;++i)
    {
        F[i][0]=b[a[i]];
        adis[i][0]=aNext[i];
        bdis[i][0]=bNext[a[i]];
    }
    for(LL i=1;i<=20;++i)
        for(LL j=1;j<=N;++j)
            if(F[ F[j][i-1] ][i-1])
            {
                F[j][i]=F[ F[j][i-1] ][i-1];
                adis[j][i]=adis[j][i-1]+adis[ F[j][i-1] ][i-1];
                bdis[j][i]=bdis[j][i-1]+bdis[ F[j][i-1] ][i-1];
            }
}
void ask1()
{
    double minNum=double(INF);
    LL ret=-1;
    for(LL i=1;i<=N;++i)
    {
        //倍增查询
        LL cur=i;
        LL totA=0,totB=0;
        double curAns=0;
        for(LL i=20;i>=0;--i)
            if(F[cur][i]&&adis[cur][i]+bdis[cur][i]+totA+totB<=X[0])
            {
                totA+=adis[cur][i];
                totB+=bdis[cur][i];
                cur=F[cur][i];
            }
        if(a[cur]&&adis[cur][0]+totA+totB<=X[0])
            totA+=adis[cur][0],cur=a[cur];
        if(totB==0) curAns=double(INF);
        else curAns=double(totA)/double(totB);
        if(curAns<minNum)
            minNum=curAns,ret=i;
    }
    printf("%lld\n",ret);
}

void ask2(LL cur,LL x)
{
    LL totA=0,totB=0;
    for(LL i=20;i>=0;--i)
        if(F[cur][i]&&adis[cur][i]+bdis[cur][i]+totA+totB<=x)
        {
            totA+=adis[cur][i];
            totB+=bdis[cur][i];
            cur=F[cur][i];
        }
    if(a[cur]&&adis[cur][0]+totA+totB<=x)
        totA+=adis[cur][0],cur=a[cur];
    printf("%lld %lld\n",totA,totB);
}
void work()
{
    calc_next();
    calc_double();
    ask1();
    for(LL i=1;i<=M;++i)
        ask2(Q[i],X[i]);
}
int main()
{
    init();
    work();
    return 0;
}
