#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cctype>
#include <cmath>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
const int INF=0x3f3f3f3f;
const int MAXN=1e5+10;
int N,M,a[MAXN],vlink[MAXN];

struct node {
    int ch[2],father;
    int sum,vv,index;
};
struct SPLAY {
    node e[MAXN*4];
    int cnt,points;
#define root e[0].ch[1]
#define lson(x) e[x].ch[0]
#define rson(x) e[x].ch[1]
#define dad(x)  e[x].father
    void connect(int x,int f,int son)
    {
        dad(x)=f,e[f].ch[son]=x;
    }
    void update(int x)
    {
        e[x].sum=e[lson(x)].sum+e[rson(x)].sum+1;
    }
    int verify(int x)
    {
        return lson(dad(x))==x;
    }
    int create(int vv,int index,int father)
    {
        ++cnt;
        memset(e+cnt,0,sizeof (node));
        e[cnt].vv=vv,e[cnt].father=father,e[cnt].sum=1,e[cnt].index=index;
        return cnt;
    }
    void destroy(int x)
    {
        memset(e+x,0,sizeof(node));
        --cnt;
    }
    void rotate(int x)
    {
        int y=dad(x),yson=verify(x);
        int mroot=dad(y),mrootson=verify(y),B=e[x].ch[yson^1];
        connect(B,y,yson),connect(y,x,yson^1),connect(x,mroot,mrootson);
        update(y),update(x);
    }
    void splay(int at,int to)
    {
        int up;
        to=dad(to);
        while( (up=dad(at)) != to )
            if(dad(up)==to) rotate(at);
            else    rotate(verify(up)==verify(at)? up:at ),rotate(at);
    }
    void build(int L,int R,int father)
    {
        if(L>R) return;
        int mid=(L+R)>>1,pos=create(a[mid],mid,father),fid=e[father].index;
        vlink[a[mid]]=pos;
        if(father==0||mid>fid)  rson(father)=pos;
        else                    lson(father)=pos;
        if(L==R)    return;
        build(L,mid-1,pos),build(mid+1,R,pos);
        update(pos);
    }
    void display(int now,int depth)
    {
        if(!now)    return;
        display(lson(now),depth+1);
        for(int i=1; i<=depth; ++i)   printf("  ");
        printf("vv=%d,index=%d,id=%d,sum=%d\n",e[now].vv,e[now].index,now,e[now].sum);
        display(rson(now),depth+1);
    }
    int getroot() {
        return root;
    }
    int rank(int id)
    {
        splay(id,root);
        return e[lson(id)].sum;
    }
    int atrank(int k)
    {
        int now=root;
        while(true)
        {
            int minused=e[now].sum-e[rson(now)].sum;
            if(k==minused)  break;
            if(k<minused)   now=lson(now);
            else            now=rson(now),k-=minused;
        }
        return e[now].vv;
    }
    void update_path(int id)
    {
        update(id);
        if(dad(id)) update_path(dad(id));
    }
    void top(int id)
    {
        splay(id,root);
        if(!rson(id))
        {
            rson(id)=lson(id);
            lson(id)=0;
        }
        else
        {
            int next=rson(id);
            while(lson(next))   next=lson(next);
            connect(lson(id),next,0);
            lson(id)=0;
            update_path(next);
            splay(next,root);
        }
    }
    void bottom(int id)
    {
        splay(id,root);
        if(!lson(id))
        {
            lson(id)=rson(id);
            rson(id)=0;
        }
        else
        {
            int next=lson(id);
            while(rson(next))   next=rson(next);
            connect(rson(id),next,1);
            rson(id)=0;
            update_path(next);
            splay(next,root);
        }
    }
} S;

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1; i<=N; ++i)   scanf("%d",a+i);
    S.build(1,N,S.getroot());
    S.display(S.getroot(),0);
    return 0;
}