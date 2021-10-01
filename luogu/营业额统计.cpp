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
int N,ans;
// code
struct node {
    int father,ch[2];
    int sum,recy,vv;
};
struct SPLAY
{
    node e[MAXN];
    int cnt,points;
#define root e[0].ch[1]
#define lson(x) e[x].ch[0]
#define rson(x) e[x].ch[1]
#define dad(x)  e[x].father
    void update(int x)
    {
        e[x].sum=e[lson(x)].sum+e[rson(x)].sum+e[x].recy;
    }
    int verify(int x)
    {
        return rson(dad(x))==x;
    }
    void connect(int x,int f,int son)
    {
        dad(x)=f,e[f].ch[son]=x;
    }
    void rotate(int x)
    {
        int y=dad(x),yson=verify(x);
        int mroot=dad(y),mrootson=verify(y);
        int B=e[x].ch[yson^1];
        connect(B,y,yson),connect(y,x,yson^1),connect(x,mroot,mrootson);
        update(y),update(x);
    }
    void splay(int at,int to)
    {
        to=dad(to);
        int up;
        while( (up=dad(at)) != to)
        {
            if(dad(up)==to) rotate(at);
            else rotate(verify(up)==verify(at)?up:at),rotate(at);
        }
    }
    int create(int vv,int father)
    {
        e[++cnt].vv=vv,e[cnt].father=father,e[cnt].sum=e[cnt].recy=1;
        return cnt;
    }
    void destroy(int id)
    {
        memset(e+id,0,sizeof (e[id]));
    }
    int build(int vv)
    {
        ++points;
        if(!cnt)
            root=create(vv,0);
        else
        {
            int now=root;
            while(true)
            {
                ++e[now].sum;
                if(e[now].vv==vv)
                {
                    ++e[now].recy;
                    return now;
                }
                int next=vv<e[now].vv?0:1;
                if(!e[now].ch[next])
                    return e[now].ch[next]=create(vv,now);
                now=e[now].ch[next];
            }
        }
        return 0;
    }
    void insert(int vv)
    {
        int id=build(vv);
        splay(id,root);
    }
    int upper(int vv)
    {
        int now=root,ret=INF;
        while(now)
        {
            if(e[now].vv>=vv&&e[now].vv<ret) ret=e[now].vv;
            if(vv<e[now].vv)    now=lson(now);
            else                now=rson(now);
        }
        return ret;
    }
    int lower(int vv)
    {
        int now=root,ret=-INF;
        while(now)
        {
            if(e[now].vv<=vv&&e[now].vv>ret)   ret=e[now].vv;
            if(vv>e[now].vv)    now=rson(now);
            else                now=lson(now);
        }
        return ret;
    }
} S;
int main()
{
    int x=0;
    scanf("%d",&N);
    scanf("%d",&x);
    S.insert(x);
    ans+=x;
    for(int i=2; i<=N; ++i)
    {
        scanf("%d",&x);
        //printf("%d lower=%d upper=%d\n",x,S.lower(x),S.upper(x));
        ans+=min(S.upper(x)-x,x-S.lower(x));
        S.insert(x);
    }
    printf("%d\n",ans);
    return 0;
}