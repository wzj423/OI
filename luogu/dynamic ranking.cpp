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
const int MAXN=10050;
int N,M;
struct node {
    int sum,l,r;
} T[MAXN*600];
int Tcnt;
int root[MAXN];
struct operation {
    char flag;
    int l,r,k,pos,t;
} O[MAXN];
int lisan[MAXN*20],lcnt;
int a[MAXN];
//data for query
int tl[40],lsize,tr[40],rsize;

#define lowbit(x)   (x&(-x))
// code
void insert(int &id,int L,int R,int pos,int vv)
{
    T[++Tcnt]=T[id];
    id=Tcnt;
    T[id].sum+=vv;
    if(L==R)    return;
    int mid=(L+R)>>1;
    if(pos<=mid)    insert(T[id].l,L,mid,pos,vv);
    else            insert(T[id].r,mid+1,R,pos,vv);
}
void pre_insert(int pos,int vv)
{
    int k=lower_bound(lisan+1,lisan+lcnt+1,a[pos])-lisan;
    for(int i=pos; i<=N; i+=lowbit(i))
        insert(root[i],1,lcnt,k,vv);
}
int query(int L,int R,int k)
{
    if(L==R)    return L;
    int mid=(L+R)>>1,sum=0;
    for(int i=1; i<=rsize; ++i)   sum+=T[ T[ tr[i] ].l ].sum;
    for(int i=1; i<=lsize; ++i)   sum-=T[ T[ tl[i] ].l ].sum;
    if(k<=sum)
    {
        for(int i=1; i<=rsize; ++i)   tr[i]=T[ tr[i] ].l;
        for(int i=1; i<=lsize; ++i)   tl[i]=T[ tl[i] ].l;
        return query(L,mid,k);
    }
    else
    {
        for(int i=1; i<=rsize; ++i)   tr[i]=T[ tr[i] ].r;
        for(int i=1; i<=lsize; ++i)   tl[i]=T[ tl[i] ].r;
        return query(mid+1,R,k-sum);        
    }
}
int pre_query(int L,int R,int k)
{
    memset(tl,0,sizeof tl);
    memset(tr,0,sizeof tr);
    lsize=rsize=0;
    for(int i=R;i;i-=lowbit(i)) tr[++rsize]=root[i];
    for(int i=L-1;i;i-=lowbit(i))   tl[++lsize]=root[i];
    return query(1,lcnt,k);
}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d",a+i);
        lisan[++lcnt]=a[i];
    }
    for(int i=1; i<=M; ++i)
    {
        scanf("%1s",&O[i].flag);
        if(O[i].flag=='Q')  scanf("%d%d%d",&O[i].l,&O[i].r,&O[i].k);
        else                scanf("%d%d",&O[i].pos,&O[i].t),lisan[++lcnt]=O[i].t;
    }
    sort(lisan+1,lisan+lcnt+1);
    lcnt=unique(lisan+1,lisan+lcnt+1)-lisan-1;
    for(int i=1;i<=N;++i)   pre_insert(i,1);
    for(int i=1;i<=M;++i)
    {
        if(O[i].flag=='Q')
        {
            int t=pre_query(O[i].l,O[i].r,O[i].k);
            printf("%d\n",lisan[t]);
        }  
        else
        {
            pre_insert(O[i].pos,-1);
            a[O[i].pos]=O[i].t;
            pre_insert(O[i].pos,1);
        }
    }
    return 0;
}