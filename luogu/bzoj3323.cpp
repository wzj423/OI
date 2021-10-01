#pra\
gma GCC optimize("O3")
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
const LL MAXN=1e5+10,mod=20130426;
int N;
LL help[MAXN*2];
// code
struct node
{
    int father,ch[2];
    LL xishu,index,sum;
    LL atag,mtag;
    ///先乘后加
};
struct SPLAY
{
    node e[3*MAXN];
    int cnt,points;

#define root e[0].ch[1]
#define lson(x) e[x].ch[0]
#define rson(x) e[x].ch[1]
#define dad(x)  e[x].father

    void update(int x)
    {
        e[x].sum=e[lson(x)].sum+e[rson(x)].sum+1;
    }
    int verify(int x)
    {
        return rson(dad(x))==x;
    }
    void connect(int x,int f,int son)
    {
        dad(x)=f,e[f].ch[son]=x;
    }
    int create(int index,int father)
    {
        ++cnt;
        memset(&e[cnt],0,sizeof (node));
        e[cnt].father=father;e[cnt].sum=1,e[cnt].mtag=1;e[cnt].index=index;
        return cnt;
    }
    void pushdown(int x)
    {
        e[x].xishu=(e[x].xishu*e[x].mtag+e[x].atag)%mod;
        if(lson(x))
        {
            e[lson(x)].atag=(e[lson(x)].atag*e[x].mtag%mod+e[x].atag)%mod;
            e[lson(x)].mtag*=e[x].mtag;
            e[lson(x)].mtag%=mod;
        }
        if(rson(x))
        {
            e[rson(x)].atag=(e[rson(x)].atag*e[x].mtag+e[x].atag)%mod;
            e[rson(x)].mtag*=e[x].mtag;
            e[rson(x)].mtag%=mod;
        }
        e[x].atag=0,e[x].mtag=1;
        e[x].xishu%=mod;
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
        to=dad(to);
        int up;
        while((up=dad(at)) != to )
            if(dad(up)==to) rotate(at);
            else    rotate( verify(up)==verify(at)?up:at),rotate(at);
    }
    void build(int L,int R,int father=0,bool isrig=true)
    {
        if(L>R) return;
        int mid=(L+R)>>1,pos=create(mid-2,father);
        connect(pos,father,isrig);
        if(L==R)    return;
        build(L,mid-1,pos,false),build(mid+1,R,pos,true);
        update(pos);
    }
    void display(int x,int dep=0)
    {
        if(!x)  return;
        display(lson(x),dep+1);
        for(int i=1; i<=dep; ++i) printf("  ");
        printf("id=%d sum=%lld xishu=%lld index=%lld atag=%lld mtag=%lld\n",x,e[x].sum,e[x].xishu,e[x].index,e[x].atag,e[x].mtag);
        display(rson(x),dep+1);
    }
    int getroot()   {return root;}
    int atrank(int k)
    {
        int now=root;
        while(true)
        {
            pushdown(now);
            int minused=e[now].sum-e[rson(now)].sum;
            if(k==minused)  break;
            if(k<minused)   now=lson(now);
            else            now=rson(now),k-=minused;
        }
        return now;
    }
    void mul_xishu(int L,int R,int x)
    {
        int lid=atrank(L),rid=atrank(R+2);
        splay(lid,root);splay(rid,rson(root));
        pushdown(lson(rid));
        e[lson(rid)].mtag*=x;
        e[lson(rid)].mtag%=mod;
    }
    void add_xishu(int L,int R,int x)
    {
        int lid=atrank(L),rid=atrank(R+2);
        splay(lid,root);splay(rid,rson(root));
        pushdown(lson(rid));
        e[lson(rid)].atag+=x;
        e[lson(rid)].atag%=mod;
    }
    void update_path(int id)
    {
        while(id)
        {
            update(id);
            id=dad(id);
        }
    }
    void add_index(int L,int R)/// lid,lef, ... rig,rid
    {
        int lid=atrank(L),rid=atrank(R+2);
        splay(lid,root),splay(rid,rson(root));
        pushdown(lson(rid));
        int lef=atrank(L+1),rig=atrank(R+1);

        int empty_pos=create(L-1,lef);
        connect(empty_pos,lef,0);

        splay(rig,lson(rid));
        e[rid].xishu=(e[rid].xishu+e[rig].xishu)%mod;
        int chd_rig=lson(rig);
        connect(chd_rig,rid,0);

        update_path(empty_pos);
        memset(e+rig,0,sizeof (node));
    }
    void calc(int id,int vv,LL& ans)
    {
        pushdown(id);
        if(rson(id)) calc(rson(id),vv,ans);
        if(e[id].index!=-1) ans=(e[id].xishu%mod+ans*vv)%mod;
        if(lson(id)) calc(lson(id),vv,ans);
    }
    void query(int vv)
    {
        vv%=mod;
        LL ans=0;
        calc(root,vv,ans);
        printf("%lld\n",ans%mod);
    }
} S;
char opt[10];
int main()
{
    S.build(1,MAXN);
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
    {
        scanf("%s",opt);
        if(opt[0]=='a')
        {
            int L,R,x;
            scanf("%d%d%d",&L,&R,&x);
            S.add_xishu(L+1,R+1,x);
        }
        else if(opt[3]=='x')
        {
            int L,R;
            scanf("%d%d",&L,&R);
            S.add_index(L+1,R+1);
        }
        else if(opt[0]=='m')
        {
            int L,R,x;
            scanf("%d%d%d",&L,&R,&x);
            S.mul_xishu(L+1,R+1,x);
        }
        else if(opt[0]=='q')
        {
            int x;
            scanf("%d",&x);
            S.query(x);
        }
    }
    return 0;
}
