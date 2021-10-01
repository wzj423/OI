/**
离散化
扫描线法
failed
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <cstring>

#include <algorithm>
#include <map>
#include <set>
#include <vector>
using namespace std;
struct node
{
    int L,R;
    int num;
    int setFlag;
} T[100010<<2];
struct edge
{
    int L,R;
    int height;
    int num;
};
vector <edge> E;
int N;
// code
bool cmp(edge a,edge b)
{
    return a.height<b.height;
}
//左闭右开建树
void clean_mark(int id)
{
    if(T[id].setFlag!=-1)
    {
        T[id].num=(T[id].R-T[id].L)*T[id].setFlag;
        if(T[id].L!=T[id].R-1)
        {
            T[id<<1].setFlag=T[id].setFlag;
            T[id<<1|1].setFlag=T[id].setFlag;
        }
    }
    T[id].setFlag=-1;
}
void build_tree(int L,int R,int id=1)
{
    T[id].L=L;
    T[id].R=R;
    T[id].setFlag=-1;
    if(L==R-1) return;
    build_tree(L,(L+R)/2,id<<1);
    build_tree((L+R)/2,R,id<<1|1);
}
void set_tree(int B,int E,int x,int id=1)
{
    //printf("%s set[%d,%d) as %d in[%d,%d) id=%d\n",__func__,B,E,x,T[id].L,T[id].R,id);
    if(B>=E)
        return;
    clean_mark(id);
    if(T[id].L==B&&T[id].R==E)
    {
        T[id].setFlag=x;
        return;
    }
    int mid=(T[id].L+T[id].R)/2;
    if(E<=mid)
    {
        set_tree(B,E,x,id<<1);
    }
    else if(B>mid)
    {
        set_tree(B,E,x,id<<1|1);
    }
    else
    {
        set_tree(B,mid,x,id<<1);
        set_tree(mid,E,x,id<<1|1);
    }
    clean_mark(id<<1);
    clean_mark(id<<1|1);
    T[id].num=T[id<<1].num+T[id<<1|1].num;
    //printf("[%d,%d)=%d=%d+%d id=%d\n",T[id].L,T[id].R,T[id].num,T[id<<1].num,T[id<<1|1].num,id);
}
int query_tree(int B,int E,int id=1)
{
    if(B==E)
        return 0;
    clean_mark(id);
    if(T[id].L==B&&T[id].R==E)
    {
        return T[id].num;
    }
    int mid=(T[id].L+T[id].R)/2;
    if(E<=mid)
    {
        return query_tree(B,E,id<<1);
    }
    else if(B>mid)
    {
        return query_tree(B,E,id<<1|1);
    }
    else
    {
        return query_tree(B,mid,id<<1)+query_tree(mid,E,id<<1|1);
    }
}
void init()
{
    memset(T,0,sizeof T);
    scanf("%d",&N);
    if(N==0)
        exit(0);
}
void work()
{
    build_tree(0,50010);
    E.clear();
    for(int i=1; i<=N; ++i)
    {
        int x1,y1,x2,y2,x3,y3,x4,y4;
        edge t;
        scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
        t.L=x1,t.R=x2,t.height=y1,t.num=1;
        E.push_back(t);
        t.height=y2,t.num=0;
        E.push_back(t);
        t.L=x3,t.R=x4,t.height=y3,t.num=0;
        E.push_back(t);
        t.height=y4,t.num=1;
        E.push_back(t);
    }
    sort(E.begin(),E.end(),cmp);
    int ans=0;
    for(int i=0; i<E.size()-1; ++i)
    {
        set_tree(E[i].L,E[i].R,E[i].num);
        ans+=query_tree(0,50010)*(E[i+1].height-E[i].height);
    }
    cout<<ans<<endl;
}
int main()
{
    while(true)
    {
        init();
        work();
    }
    return 0;
}



