/**
自动售票系统
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>


using namespace std;
int C,S,Q;
struct node
{
    int l;
    int r;
    int minNum;
    int mark;
} T[60010*4];
void clean_node(int id)
{
    T[id].minNum-=T[id].mark;
    if(T[id].l!=T[id].r)
    {
        T[id<<1].mark+=T[id].mark;
        T[id<<1|1].mark+=T[id].mark;
    }
    T[id].mark=0;
}
void make_tree(int b,int e,int id=1)
{
    T[id].l=b;
    T[id].r=e;
    if(b==e)
    {
        T[id].minNum=S;
        return;
    }
    make_tree(b,(b+e)/2,id<<1);
    make_tree((b+e)/2+1,e,id<<1|1);
    T[id].minNum=S;
}
bool query_tree(int b,int e,int need,int id=1)
{
    clean_node(id);
    cout<<__func__<<"    "<<id<<endl;
    if(b==T[id].l&&e==T[id].r)
    {
        return T[id].minNum-T[id].mark-need>=0;
    }
    int mid=(T[id].l+T[id].r)/2;
    if(b>mid)
    {
        return query_tree(b,e,need,id<<1|1);
    }
    else if(e<=mid)
    {
        return query_tree(b,e,need,id<<1);
    }
    else
    {
        return query_tree(b,mid,need,id<<1)&&query_tree(mid+1,e,need,id<<1|1);
    }
}
void modify_tree(int b,int e,int need,int id=1)
{
    clean_node(id);
    if(b==T[id].l&&e==T[id].r)
    {
        T[id].mark+=need;
        clean_node(id);
        return;
    }
    int mid=(T[id].l+T[id].r)/2;
    if(b>mid)
    {
        modify_tree(b,e,need,id<<1|1);
    }
    else if(e<=mid)
    {
        modify_tree(b,e,need,id<<1);
    }
    else
    {
        modify_tree(b,mid,need,id<<1);
        modify_tree(mid+1,e,need,id<<1|1);
    }
}
int main()
{
    scanf("%d%d%d",&C,&S,&Q);
    int O,D,N;
    make_tree(1,C);
    for(int i=1;i<=Q;++i)
    {
        scanf("%d%d%d",&O,&D,&N);
        if(query_tree(O,D,N))
        {
            puts("YES");
            modify_tree(O,D,N);
        }
        else
        {
            puts("NO");
        }
    }
    return 0;
}
