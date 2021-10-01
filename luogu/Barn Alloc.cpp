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
const int INF=0x3f3f3f3f;
struct node
{
    int vv;
    int L,R;
    int mark;
} T[100010*5];
int N,M;
int a[100010];
struct seg{int b,e;}S[100100];
int ans=0;
// code
bool cmp(seg a,seg b)
{
    if(a.e!=b.e)    return a.e<b.e;
    else return a.b>b.b;
}

void clean_mark(int id)
{
    T[id].vv+=T[id].mark;
    if(T[id].L!=T[id].R)
    {
        T[id<<1].mark+=T[id].mark;
        T[id<<1|1].mark+=T[id].mark;
    }
    T[id].mark=0;
}
void build_tree(int L,int R,int id=1)
{
    T[id].L=L,T[id].R=R;
    if(L!=R)
    {
        build_tree(L,(L+R)/2,id<<1);
        build_tree((L+R)/2+1,R,id<<1|1);
        T[id].vv=min(T[id<<1].vv,T[id<<1|1].vv);
    }
    else
        T[id].vv=a[L];
}
void modify(int id,int B,int E,int x)
{
    clean_mark(id);
    if(T[id].L>=B&&T[id].R<=E)
    {
        T[id].mark+=x;
        return;
    }
    else if(T[id].R<B||T[id].L>E)   return;
    modify(id<<1,B,E,x);
    modify(id<<1|1,B,E,x);
    clean_mark(id<<1),clean_mark(id<<1|1);
    T[id].vv=min(T[id<<1].vv,T[id<<1|1].vv);
}
int query(int id,int B,int E)
{
    clean_mark(id);
    if(T[id].L>=B&&T[id].R<=E)
    {
        return T[id].vv;
    }
    else if(T[id].R<B||T[id].L>E)   return INF;
    return min( query(id<<1,B,E) , query(id<<1|1,B,E) );    
}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)   scanf("%d",a+i);
    build_tree(1,N);
    for(int i=1;i<=M;++i)   scanf("%d%d",&S[i].b,&S[i].e);
    sort(S+1,S+M+1,cmp);
    for(int i=1;i<=M;++i)
    {
        if( query(1,S[i].b,S[i].e) >=1 )
        {
            ++ans;
            modify(1,S[i].b,S[i].e,-1);
            //printf("seg %d [%d,%d] has been put!\n",i,S[i].b,S[i].e);
        }
        else
        {
            //printf("seg %d [%d,%d] minval is %d!\n",i,S[i].b,S[i].e,query(1,S[i].b,S[i].e));
        }
    }
    printf("%d\n",ans);
    return 0;
}