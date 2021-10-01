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
const int maxn=1e6+10;
int N,M;
int a[maxn];
struct node{
    int l,r,vv;
}T[maxn*32];
int Tcnt;
int root[maxn];
// code
void build_tree(int &id,int L,int R)
{
    T[++Tcnt]=T[id];
    id=Tcnt;
    int mid=(L+R)>>1;    
    if(L==R)    T[id].vv=a[L];
    else        build_tree(T[id].l,L,mid),build_tree(T[id].r,mid+1,R); 
    //printf("build id=%d of [%d,%d] vv=%d\n",id,L,R,T[id].vv);       
}
void modify(int &id,int x,int to,int L,int R)
{
    T[++Tcnt]=T[id];
    id=Tcnt;
    if(L==R)
    {
        T[id].vv=x;
        return;
    }
    int mid=(L+R)>>1;
    if(to<=mid)     modify(T[id].l,x,to,L,mid);
    else            modify(T[id].r,x,to,mid+1,R);
}
int query(int id,int to,int L,int R)
{
    //printf("query id=%d [%d] in [%d,%d]\n",id,to,L,R);
    if(L==R)    return T[id].vv;
    int mid=(L+R)>>1;
    if(to<=mid) return query(T[id].l,to,L,mid);
    else        return query(T[id].r,to,mid+1,R);
}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)   scanf("%d",a+i);
    build_tree(root[0],1,N);
    for(int i=1;i<=M;++i)
    {
        int ver,flag,index,x;
        scanf("%d%d",&ver,&flag);
        root[i]=root[ver];
        if(flag==1)
        {
            scanf("%d%d",&index,&x);
            modify(root[i],x,index,1,N);
        }
        else
        {
            scanf("%d",&index);
            int ret=query(root[i],index,1,N);
            printf("%d\n",ret);
        }
    }
    return 0;
}