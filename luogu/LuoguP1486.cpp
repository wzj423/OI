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
int N,MinPaid,ChangeVal,totLeave;

struct node
{
    int father,ch[2];
    int sum,recy;
    int vv;
};
struct SPLAY
{
    node e[MAXN*4];
    int cnt,points;
#define root e[0].ch[1]
#define lson(x) e[x].ch[0]
#define rson(x) e[x].ch[1]
#define dad(x)  e[x].father
    void update(int x)
    {
        e[x].sum=e[lson(x)].sum+e[rson(x)].sum+e[x].recy;
    }
    void connect(int x,int f,int son)
    {
        dad(x)=f;
        e[f].ch[son]=x;
    }
    int verify(int x)
    {
        return rson(dad(x))==x;
    }
    int create(int vv,int father)
    {
        memset(e+cnt+1,0,sizeof (node));
        e[++cnt].vv=vv,dad(cnt)=father,e[cnt].sum=e[cnt].recy=1;
        return cnt;
    }
    void destroy(int id)
    {
        memset(e+id,0,sizeof (e[id]));
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
        while( (up=dad(at)) != to )
            if(dad(up)==to) rotate(at);
            else    rotate( verify(up)==verify(at) ?up:at),rotate(at);
    }
    int atrank(int k)
    {
        if(k>points)    return -1;
        int now=root;
        while(true)
        {
            int minused=e[now].sum-e[lson(now)].sum;
            if(e[rson(now)].sum<k&&k<=minused)   break;
            if(k<=minused)  now=rson(now);
            else            now=lson(now),k-=minused;
        }
        splay(now,root);
        return e[now].vv;
    }
    int build(int vv)
    {
        ++points;
        if(!cnt)
        {
            root=create(vv,0);
        }
        else
        {
            int now=root;
            while(true)
            {
                ++e[now].sum;
                if(vv==e[now].vv)
                {
                    ++e[now].recy;
                    return now;
                }
                int next=vv<e[now].vv?0:1;
                if(!e[now].ch[next])    return e[now].ch[next]=create(vv,now);
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
    void delete_lower(int vv)//
    {
        int now=root,result=INF,id=-1;
        while(now)
        {
            if(e[now].vv>=vv&&e[now].vv<result) result=e[now].vv,id=now;
            if(vv<e[now].vv)    now=lson(now);
            else                now=rson(now);
        }
        if(id!=-1)
        {
            splay(id,root);
            totLeave+=e[lson(id)].sum;
            points-=e[lson(id)].sum;
            lson(id)=0;
            update(id);
        }
        else
        {
            totLeave+=e[root].sum;
            cnt=points=0;
            root=0;
            memset(&e[0],0,sizeof (e[0]));
        }
    }

} S;

char opt[10];
int main()
{
    scanf("%d%d",&N,&MinPaid);
    for(int i=1; i<=N; ++i)
    {
        int x;
        scanf("%s",opt);
        scanf("%d",&x);
        if(opt[0]=='I')
        {
            if(x<MinPaid)   continue;
            S.insert(x-ChangeVal);
        }
        else if(opt[0]=='A')
        {
            ChangeVal+=x;
        }
        else if(opt[0]=='S')
        {
            ChangeVal-=x;
            S.delete_lower(MinPaid-ChangeVal);
        }
        else if(opt[0]=='F')
        {
            int t=S.atrank(x);
            if(t!=-1)
                printf("%d\n",t+ChangeVal);
            else
                puts("-1");
        }
    }
    printf("%d\n",totLeave);
    return 0;
}