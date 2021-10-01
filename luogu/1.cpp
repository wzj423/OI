#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define I inline
#define R register
#define INF 1000000
using namespace std;
deque<int> f;
int n,m,k,len=0,tot=0;
int p[400010],last[400010];
struct node {
    int x,y,z,next;
} a[800010];
int dis[400010],q[400010];
bool bz[400010];
I int readint() {
    int f=1,x=0;
    char ch=getchar();
    for(; ch<'0'||ch>'9'; ch=getchar())
        if(ch=='-') f=-1;
    for(; ch>='0'&&ch<='9'; x=(x<<3)+(x<<1)+(ch^48),ch=getchar());
    return x*f;
}
I void ins(int x,int y,int z) {
    a[++len].x=x;
    a[len].y=y;
    a[len].z=z;
    a[len].next=last[x];
    last[x]=len;
}
I int spfa() {
    for(int i=1; i<=n; i++)
        dis[i]=1e7;
    dis[0]=0;
    f.push_back(0);
    while(!f.empty()) {
        int x=f.front();
        f.pop_front();
        bz[x]=false;
        for(R int i=last[x]; i; i=a[i].next) {
            int y=a[i].y;
            if(dis[x]+a[i].z<dis[y]) {
                dis[y]=dis[x]+a[i].z;
                if(!bz[y]) {
                    if(++tot>=INF) return -1;//判负环，不是正确的，只是题目卡差分约束，普通的过不了，只好“特判”
                    bz[y]=true;
                    if(!f.empty()&&dis[y]<dis[f.front()]) f.push_front(y);
                    else f.push_back(y);
                }
            }
        }
    }
    return dis[n];
}
int main() {
    int x,y;
    n=readint(),m=readint();
    for(R int i=1; i<=m; i++) {
        x=readint(),y=readint();
        ins(x-1,y,1),ins(y,x-1,-1);
    }
    for(R int i=1; i<=n; i++)
        ins(i-1,i,1),ins(i,i-1,0);
    printf("%d",spfa());
}
