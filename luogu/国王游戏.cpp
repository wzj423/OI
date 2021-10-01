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
struct _p
{
    LL a,b;
}P[1010];
int N;
LL ans[40010];//万进制高精
LL tmp[40010];//临时变量
LL tot[40010];
const int lendit=40005;
// code
bool cmp(_p a,_p b)
{
    return a.a*a.b<b.a*b.b;
}
void init()
{
    scanf("%d",&N);
    scanf("%lld%lld",&P[0].a,&P[0].b);
    for(int i=1;i<=N;++i)
        scanf("%lld%lld",&P[i].a,&P[i].b);
    sort(P+1,P+N+1,cmp);
    //for(int i=0;i<=N;++i)
     //   printf("%lld %lld\n",P[i].a,P[i].b);
    ans[0]=1;ans[lendit]=1;
    tmp[0]=1;tmp[lendit]=1;
    tot[0]=1;tot[lendit]=1;
}
void display(LL *num)
{
    printf("%lld",num[num[lendit]-1]);
    for(int i=num[lendit]-2; i>=0; i--)
        printf("%04lld",num[i]);
    cout<<endl;
}
void mul(LL *a,int x)
{
    int carry=0;
    for(int i=0;i<a[lendit];++i)
    {
        a[i]*=x;
        a[i]+=carry;
        carry=0;
        int t=a[i]/10000;
        a[i]%=10000;
        carry+=t;
    }
    a[a[lendit]]+=carry;
    if(a[a[lendit]]!=0)
        a[lendit]++;
    //display(a);
}
void div(LL *a,int x)
{
    //puts(__func__);
    static LL t[40010];
    memset(t,0,sizeof t);
    int borrow=0;
    for(int i=a[lendit]-1;i>=0;--i)
    {
        LL tmp=a[i]+borrow*10000;
        t[i]=tmp/x;
        borrow=tmp%x;
    }
    t[lendit]=a[lendit];
    while(t[t[lendit]-1]==0&&t[lendit]>1) --t[lendit];
    //printf("len is %d\n",t[lendit]);
    memcpy(a,t,sizeof t);
    //display(a);
}
bool compare(LL * a,LL * b)// return a<b
{
    if(a[lendit]!=b[lendit])
        return a[lendit]<b[lendit];
    for(int i=a[lendit]-1;i>=0;--i)
    {
        if(a[i]!=b[i])
            return a[i]<b[i];
    }
    return false;
}
void work()
{
    for(int i=0;i<=N;++i)
    {

        memcpy(tmp,tot,sizeof tot);
        div(tmp,P[i].b);
        //display(tmp);
        if(compare(ans,tmp))
            memcpy(ans,tmp,sizeof tmp);
        mul(tot,P[i].a);
    }
    display(ans);
}
int main()
{
    init();
    work();
    //system("pause");
    return 0;
}