/**
线段树

没有懒标记 70
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
typedef long long int LL;
struct node
{
    LL l;
    LL r;
    LL sum;
    LL addMark;
} tree[400010];
LL a[100010];
LL N,M;
void cleanMark(LL id)
{
    tree[id].sum+=(tree[id].r-tree[id].l+1)*tree[id].addMark;
    if(tree[id].l!=tree[id].r)
    {
        tree[id<<1].addMark+=tree[id].addMark;
        tree[id<<1|1].addMark+=tree[id].addMark;
    }
    tree[id].addMark=0;
}
void make_tree(LL index,LL b,LL e)
{
    tree[index].l=b;
    tree[index].r=e;
    if(b==e)
    {
        tree[index].sum=a[b];
        return ;
    }
    make_tree(index*2,b,(b+e)/2);
    make_tree(index*2+1,(b+e)/2+1,e);
    tree[index].sum=tree[index*2].sum+tree[index*2+1].sum;

}
#define DEBUG while(0)cout
void display()
{
    for(int i=1; i<=2*N; i++)
        cout<<tree[i].l<<","<<tree[i].r<<"\t"<<tree[i].sum<<endl;
}
LL query_tree(LL b,LL e,LL index = 1l)
{
    cleanMark(index);
    if(tree[index].l==b&&tree[index].r==e)
        return tree[index].sum;
    LL mid=(tree[index].l+tree[index].r)/2;
    if(mid>=e)
    {
        return query_tree(b,e,index*2);
    }
    if(mid<b)
    {
        return query_tree(b,e,index*2+1);
    }
    return query_tree(b,mid,index*2)+query_tree(mid+1,e,index*2+1);
}
void modify_tree(LL b,LL e,LL k,LL index =1l)
{
    cleanMark(index);
    /*if(b==e&&tree[index].l==tree[index].r)
    {
        tree[index].sum+=k;
        return;
    }*/
    if(b==tree[index].l&&e==tree[index].r)
    {
        tree[index].addMark+=k;
        return;
    }
    LL mid = (tree[index].l+tree[index].r)/2;
    if(mid>=e)
    {
        modify_tree(b,e,k,index*2);
    }
    else if(mid<b)
    {
        modify_tree(b,e,k,index*2+1);
    }
    else
    {
        modify_tree(b,mid,k,index*2);
        modify_tree(mid+1,e,k,index*2+1);
    }
    //tree[index].sum=tree[index*2].sum+tree[index*2+1].sum;
}
int main()
{
    scanf("%lld%lld",&N,&M);
    for(int i=1; i<=N; ++i)
        scanf("%lld",&a[i]);
    make_tree(1,1,N);
    LL b,x,y,k;
    for(int i=1; i<=M; ++i)
    {
        scanf("%lld",&b);
        if(b==1)
        {
            scanf("%lld%lld%lld",&x,&y,&k);
            modify_tree(x,y,k);
        }
        else
        {
            scanf("%lld%lld",&x,&y);
            printf("%lld\n",query_tree(x,y));
        }
    }
    return 0;
}
