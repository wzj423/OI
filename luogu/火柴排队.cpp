#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include<string>

#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;
typedef long long LL;
int N;
struct data
{
    int vv;
    int id;
};
data a[100010];
data b[100010];
int tar[100010];
int help[100010];
LL ans=0;
// code
bool cmpVal(data x,data y)
{
    return x.vv<y.vv;
}
void reid()
{
    sort(a+1,a+N+1,cmpVal);
    sort(b+1,b+N+1,cmpVal);
    for(int i=1;i<=N;++i)
        tar[a[i].id]=b[i].id;
}
void init()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
        scanf("%d",&a[i].vv),a[i].id=i;
    for(int i=1;i<=N;++i)
        scanf("%d",&b[i].vv),b[i].id=i;
    reid();
}
void merge_sort(int L,int R)
{
    LL t=0;
    if(L==R)    return;
    int mid=(L+R)>>1;
    merge_sort(L,mid);
    merge_sort(mid+1,R);
    int pl=L,pr=mid+1;
    /*for(int i=L;i<=R;++i)
    {
        if(pl>mid) help[i]=D[pr++].second;
        else if(pr>R) help[i]=D[pl++].second;
        else if(D[pl].second<=D[pr].second)
        {
            help[i]=D[pl++].second;
        }
        else
        {
            t+=mid+1-pl;
            help[i]=D[pr++].second;
            //ans+=pr-mid;

        }
    }*/
    int ph=L;
    while(pl<=mid&&pr<=R)
    {
        if(tar[pl]>tar[pr])
        {
            ans+=mid-pl+1;
            help[ph++]=tar[pr++];
        }
        else help[ph++]=tar[pl++];
    }
    while(pl<=mid) help[ph++]=tar[pl++];
    while(pr<=R) help[ph++]=tar[pr++];
    for(int i=L;i<=R;++i)
    {
        tar[i]=help[i];
    }
    ans%=99999997;
    //printf("%s in [%d,%d] num is %d\n",__func__,L,R,t);
}
void work()
{
    merge_sort(1,N);
    printf("%lld\n",ans);
}
int main()
{
    freopen("MatchNOIP2013.in","r+",stdin);
    freopen("MatchNOIP2013.out","w+",stdout);
    init();
    work();
    return 0;
}