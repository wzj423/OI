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
const int maxn=5e5+10;
struct node{
    int l,r,sum;
}T[maxn<<6];
int Tcnt;
int Root[maxn],a[maxn];
int N,M;

// code
void insert(int &id,int pos,int vv,int L,int R)
{
    T[++Tcnt]=T[id];
    id=Tcnt;
    T[id].sum+=vv;
    int mid=(L+R)>>1;
    if(L==R)    return;
    if(pos<=mid)    insert(T[id].l,pos,vv,L,mid);
    else            insert(T[id].r,pos,vv,mid+1,R);
}
int query(int lid,int rid,int x,int L,int R)
{
    if(L==R)    return L;
    int mid=(L+R)>>1;
    if(2*( T[ T[rid].l ].sum- T[ T[lid].l ].sum) >x )   return query(T[lid].l,T[rid].l,x,L,mid);
    if(2*( T[ T[rid].r ].sum- T[ T[lid].r ].sum) >x )   return query(T[lid].r,T[rid].r,x,mid+1,R);
    return 0;    
}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)   scanf("%d",a+i);
    for(int i=1;i<=N;++i)   Root[i]=Root[i-1],insert(Root[i],a[i],1,1,N);
    for(int i=1;i<=M;++i)
    {
        int L,R;
        scanf("%d%d",&L,&R);
        printf("%d\n",query(Root[L-1],Root[R],R-L+1,1,N) );
    }

    return 0;
}