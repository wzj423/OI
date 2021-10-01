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
struct node {
    int vv,father,ch[2],sum,recy;
};
struct Splay
{
#define root e[0].ch[1]
#define lson(x) e[x].ch[0]
#define rson(x) e[x].ch[1]
#define dad(x)  e[x].father
    node e[MAXN*4];
    int cnt,points;//cnt维护节点池,points维护权值数 {1,2,3,3,3} 权值数为五,节点数为三

    void update(int x)
    {
        e[x].sum=e[lson(x)].sum+e[rson(x)].sum+e[x].recy;
    }
    int verify(int x)
    {
        return lson(dad(x))==x?0:1;
    }
    void connect(int x,int f,int son)
    {
        e[x].father=f,e[f].ch[son]=x;
    }
    void rotate(int x)
    {
        int y=dad(x);
        int yson=verify(x);
        int mroot=dad(y);
        int mrootson=verify(y);
        int B=e[x].ch[yson^1];
        connect(B,y,yson),connect(y,x,yson^1),connect(x,mroot,mrootson);
        update(y);update(x);
    }
    void splay(int at,int to)
    {
        to=dad(to);
        int up=dad(at);
        while( (up=dad(at)) != to )
            if(dad(up)==to) rotate(at);
            else rotate(verify(up)==verify(at)?up:at),rotate(at);
    }
    int create(int vv,int father)
    {
        e[++cnt].vv=vv;e[cnt].father=father,e[cnt].sum=e[cnt].recy=1;
        return cnt;
    }
    void destroy(int id)
    {
        memset(e+id,0,sizeof (node));
        --cnt;
    }
    int find(int vv)
    {
        int now=root;
        while(true)
        {
            if(e[now].vv==vv)
            {
                splay(now,root);
                return now;
            }
            int next=vv<e[now].vv?0:1;
            if(!e[now].ch[next])    return 0;
            now=e[now].ch[next];
        }
    }
    int build(int vv)//无splay
    {
        ++points;
        if(!cnt)
            root=create(vv,0);//创建根节点
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
    void erase(int vv)
    {
        int deal=find(vv);
        if(!deal)   return;
        --points;
        if(e[deal].recy>1)//有重叠
        {
            --e[deal].sum,--e[deal].recy;
            return;
        }
        if(!lson(deal))//无左子树
        {
            root=rson(deal);
            dad(root)=0;
        }
        else
        {
            int lef=lson(deal);
            while(rson(lef))    lef=rson(lef);
            splay(lef,lson(deal));
            int rig=rson(deal);
            connect(rig,lef,1),connect(lef,0,1);
            update(lef);
        }
        destroy(deal);
    }
    void display(int id)
    {
        printf("vv=%d sum=%d recy=%d lson=%d rson=%d fa=%d\n",e[id].vv,e[id].sum,e[id].recy,e[lson(id)].vv,e[rson(id)].vv,e[dad(id)].vv);
    }
    int upper(int vv)//后继
    {
        int now=root,result=INF,ret=-1;
        while(now)
        {
            if(e[now].vv>vv&&e[now].vv<result)  result=e[now].vv,ret=now;
            if(vv<e[now].vv)    now=lson(now);
            else                now=rson(now);//等于也要向右走,有可能更大
        }
        return ret;
    }
    int lower(int vv)//前驱
    {
        int now=root,result=-INF,ret=-1;
        while(now)
        {
            if(e[now].vv<vv&&e[now].vv>result)  result=e[now].vv,ret=now;
            if(vv>e[now].vv)    now=rson(now);
            else                now=lson(now);
        }        
        return ret;
    }
#undef root
#undef lson
#undef rson
#undef dad
} S;


int N,tag,ans;//tag 宠物数量 减去人的数量
void pairing(int vv)
{
    //printf("pairing %d\n",vv);
    int minv=INF;
    int frontid=S.lower(vv),nextid=S.upper(vv),target=INF;
    //printf("frontid=%d vv=%d nextid=%d vv=%d\n",frontid,S.e[frontid].vv,nextid,S.e[nextid].vv);
    if(frontid!=-1) minv=vv-S.e[frontid].vv,target=S.e[frontid].vv;
    if(nextid!=-1 &&(frontid==-1||S.e[nextid].vv-vv<minv) ) minv=S.e[nextid].vv-vv,target=S.e[nextid].vv;
    ans+=minv;
    //printf("minv=%d target=%d\n\n",minv,target);
    S.erase(target);
    ans%=1000000;
}
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
    {
        int flag,x;
        scanf("%d%d",&flag,&x);
        if(flag==0)
        {
            if(tag>=0)
                S.insert(x);
            else    pairing(x);
            ++tag;
        }
        else
        {
            if(tag<=0)   S.insert(x);
            else    pairing(x);
            --tag;
        }
    }
    printf("%d\n",ans);
    return 0;
}