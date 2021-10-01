/**
线段树动态
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
struct node
{
    int lc,rc;
    int sum;
}T[100000<<2];
int Tcnt=1;
int N;
int W;
int root=1;//根
// code
void createNode(int & id)
{
    id=++Tcnt;
}
void add(int &id,int L,int R,int numId,int numAdd)
{
    if(!id) createNode(id);//动态开点
    T[id].sum+=numAdd;//区间和更新
    int mid=(L+R)>>1;
    if(L==R&&R==numId)
        return;
    if(numId<=mid)
        add(T[id].lc,L,mid,numId,numAdd);
    else
        add(T[id].rc,mid+1,R,numId,numAdd);
}
int query(int id,int L,int R,int B,int E)// [L,R]当前节点范围.[B,E]区间查询范围
{
    if(!id) return 0;
    int mid=(L+R)>>1;
    if(L==B&&R==E)
        return T[id].sum;
    if(E<=mid)
        return query(T[id].lc,L,mid,B,E);
    else if(B>mid)
        return query(T[id].rc,mid+1,R,B,E);
    else return query(T[id].lc,L,mid,B,mid)+query(T[id].rc,mid+1,R,mid+1,E);
}
int main()
{
    scanf("%d%d",&N,&W);
    char f;
    int a,b;
    for(int i=1;i<=W;++i)
    {
        cin>>f>>a>>b;
        if(f=='x')
            add(root,1,N,a,b);
        else
            printf("%d\n",query(1,1,N,a,b));
    }
    return 0;
}