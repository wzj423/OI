/**
高级线段树
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
struct Node//! 先乘再加
{
    long long addMark;
    long long mulMark;
    long long l,r;
    long long sum;
} T[800010];
long long N,P,M;
long long a[100010];
/// code
inline long long rd()
{
    long long ret;
    char c;
    int sgn;
    if(c=getchar(),c==EOF) return 0; //EOF
    while(c!='-'&&(!isdigit(c))) c=getchar();
    sgn=(c=='-')?-1:1;
    ret=(c=='-')?0:(c-'0');
    while(c=getchar(),isdigit(c)) ret=ret*10+(c-'0');
    ret*=sgn;
    return ret;
}
void cleanMark(long long id)/// 先乘再加
{
    /*T[id].sum=(T[id].sum%P*T[id].mulMark%P)%P;
    T[id].sum+=(T[id].r-T[id].l+1)*(T[id].addMark%P);*/
    T[id].sum=(T[id].sum*T[id].mulMark+T[id].addMark*(T[id].r-T[id].l+1))%P;

    if(T[id].l!=T[id].r)/// 有子节点
    {
        T[id<<1].addMark=(T[id<<1].addMark*T[id].mulMark+T[id].addMark)%P;/// 更新加法标记
        T[id<<1].mulMark=(T[id<<1].mulMark*T[id].mulMark)%P;

        T[id<<1|1].addMark=(T[id<<1|1].addMark*T[id].mulMark+T[id].addMark)%P;/// 更新加法标记
        T[id<<1|1].mulMark=(T[id<<1|1].mulMark*T[id].mulMark)%P;
    }

    T[id].addMark=0;
    T[id].mulMark=1;
}
void build_tree(int L,int R,int id=1)
{
    T[id].l=L;
    T[id].r=R;
    T[id].mulMark=1;
    if(L==R)
    {
        T[id].sum=a[L]%P;
        return;
    }
    build_tree(L,(L+R)/2,id<<1);
    build_tree((L+R)/2+1,R,id<<1|1);
    T[id].sum=(T[id<<1].sum+T[id<<1|1].sum)%P;
}
long long query_tree(int L,int R,int id=1)
{
    cleanMark(id);
    if(T[id].l==L&&T[id].r==R)
    {
        return T[id].sum;
    }
    long long mid=(T[id].l+T[id].r)/2;
    if(L>mid)
    {
        return query_tree(L,R,id<<1|1);
    }
    if(R<=mid)
    {
        return query_tree(L,R,id<<1);
    }
    return (query_tree(L,mid,id<<1)+query_tree(mid+1,R,id<<1|1));
}
void add_tree(int L,int R,int  addNum,int id=1)
{
    cleanMark(id);
    if(T[id].l==L&&T[id].r==R)
    {
        T[id].addMark+=addNum;
        //T[id].addMark%=P;
        return;
    }

    long long mid=(T[id].l+T[id].r)/2;
    /*T[id].sum+=(R-L+1)*addNum;
    T[id].sum%=P;*/
    if(L>mid)
    {
        add_tree(L,R,addNum,id<<1|1);
        cleanMark(id<<1|1);
        cleanMark(id<<1);
    }
    else if(R<=mid)
    {
        add_tree(L,R,addNum,id<<1);
        cleanMark(id<<1|1);
        cleanMark(id<<1);
    }
    else
    {
        add_tree(L,mid,addNum,id<<1);
        add_tree(mid+1,R,addNum,id<<1|1);

        cleanMark(id<<1|1);
        cleanMark(id<<1);
    }
    T[id].sum=T[id<<1].sum+T[id<<1|1].sum;
}
void mul_tree(int L,int R,int mulNum,int id=1)
{
    if(T[id].l==L&&T[id].r==R)
    {
        T[id].mulMark*=mulNum;
        T[id].mulMark%=P;
        T[id].addMark*=mulNum;
        T[id].addMark%=P;
        return;
    }
    cleanMark(id);
    int mid=(T[id].l+T[id].r)/2;
    if(L>mid)
    {
        mul_tree(L,R,mulNum,id<<1|1);
        cleanMark(id<<1|1);
        cleanMark(id<<1);
    }
    else if(R<=mid)
    {
        mul_tree(L,R,mulNum,id<<1);
        cleanMark(id<<1|1);
        cleanMark(id<<1);
    }
    else
    {
        mul_tree(L,mid,mulNum,id<<1);
        mul_tree(mid+1,R,mulNum,id<<1|1);

        cleanMark(id<<1);
        cleanMark(id<<1|1);
    }
    T[id].sum=T[id<<1].sum+T[id<<1|1].sum;
}
void init()
{
    //scanf("%lld%lld",&N,&P);
    N=rd();
    P=rd();
    for(int i=1; i<=N; ++i)
    {
        //scanf("%lld",&a[i]);
        a[i]=rd();
    }
    build_tree(1,N);
}
void work()
{
    long long M;
    //scanf("%lld",&M);
    M=rd();
    while(M--)
    {
        long long b,e,c;
        long long bb;
        //scanf("%lld",&bb);
        bb=rd();
        if(bb==1)
        {
            //scanf("%lld%lld%lld",&b,&e,&c);
            b=rd();
            e=rd();
            c=rd();
            mul_tree(b,e,c);
        }
        else if(bb==2)
        {
            //scanf("%lld%lld%lld",&b,&e,&c);
            b=rd();
            e=rd();
            c=rd();
            add_tree(b,e,c);
        }
        else
        {
            //scanf("%lld%lld",&b,&e);
            b=rd();
            e=rd();
            printf("%lld\n",query_tree(b,e)%P);
        }
    }
}
int main()
{
    freopen("seqb.in","r+",stdin);
    freopen("seqb.out","w+",stdout);
    init();
    work();
    return 0;
}
