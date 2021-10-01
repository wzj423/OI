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
const LL INF=0x3f3f3f3f;
LL N,M;
LL a[500010];
struct node
{
    LL atag,sum;
} T[500010<<3];
// code
void build_tree(LL L,LL R,LL id=1)
{
    if(L==R)
        T[id].sum=a[L];
    else
    {
        build_tree(L,(L+R)/2,id<<1);
        build_tree((L+R)/2+1,R,id<<1|1);
        T[id].sum=T[id<<1].sum+T[id<<1|1].sum;
    }
}
void clean_mark(LL id,LL L,LL R)
{
    if(T[id].atag)
        T[id].sum+=(R-L+1)*T[id].atag;
    if(L!=R)
        T[id<<1].atag+=T[id].atag, T[id<<1|1].atag+=T[id].atag;
    T[id].atag=0;
}
void add(LL B,LL E,LL x,LL L,LL R,LL id=1)
{
    if(L>E||R<B)
        return;
    clean_mark(id,L,R);
    if(L>=B&&R<=E)
    {
        T[id].atag+=x;
        return;
    }
    LL mid=(L+R)>>1;
    add(B,E,x,L,mid,id<<1);
    add(B,E,x,mid+1,R,id<<1|1);
    clean_mark(id<<1,L,mid);
    clean_mark(id<<1|1,mid+1,R);
    T[id].sum=T[id<<1].sum+T[id<<1|1].sum;
}
LL query(LL B,LL E,LL L,LL R,LL id=1)
{
    if(L>E||R<B)
        return 0;
    //printf("query [%d,%d] in [%d,%d] id=%d\n",B,E,L,R,id);
    clean_mark(id,L,R);
    if(L>=B&&R<=E)
        return T[id].sum;
    LL mid=(L+R)>>1;
    return query(B,E,L,mid,id<<1) + query(B,E,mid+1,R,id<<1|1);
}
void calc_force(LL L,LL R,LL p)
{
    //printf("calc_force (%d,%d,%d)\n",L,R,p);
    LL ans=query(R,R,1,N);
    for(LL i=R-1; i>=L; --i)
    {
        LL base=query(i,i,1,N),index=ans;
        ans=1;
        for(LL k=1; k<=index; ++k)
        {
            ans*=base;
        }
        //printf("[%d,%d]%% %d = %d\n",i,R,p,ans);
    }
    printf("%lld\n",ans);
}
LL qm(LL a,LL b,LL mod)
{
    LL ans=1,base=a;
    while(b!=0)
    {
        if(b&1!=0)
            ans*=base,ans%=mod;
        base*=base;
        base%=mod;
        b>>=1;
    }
    return ans;
}
int main()
{
    scanf("%lld%lld",&N,&M);
    for(LL i=1; i<=N; ++i)
        scanf("%lld",a+i);

    build_tree(1,N);
    //printf("%lld\n",qm(3,27,10000));
    for(LL i=1; i<=M; ++i)
    {
        LL b,l,r,x;
        scanf("%lld%lld%lld%lld",&b,&l,&r,&x);
        if(b==1)
            add(l,r,x,1,N);
        else
        {
            if(x==1)    printf("0\n");
            else if(x==2)
            {
                LL vv=query(l,l,1,N);
                printf("%lld\n",vv%x);
            }
            else if(l==r)
            {
                printf("%lld\n",query(l,l,1,N)%x);
            }
            else if(r-l==1)
            {
                int a=query(l,l,1,N)%x,b=query(r,r,1,N);
                printf("%lld\n",qm(a,b,x));
            }
            else
            {
                calc_force(l,r,x);
            }
        }
    }
    return 0;
}
