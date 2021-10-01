#include <bits/stdc++.h>
const int MAXN = 1e5 + 10, MAXK = 2e5 + 10;
typedef long long ll;
//tool ================================
using namespace std;
inline int rd()
{
    int x=0,f=1;
    char ch=getchar();
    while(isdigit(ch)==0 && ch!='-')ch=getchar();
    if(ch=='-')f=-1,ch=getchar();
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}
//def=====================================
int N, K, cnt;
struct node {
    int x, y, z;
    int ans, w;
} a[MAXN], b[MAXN];
int ans[MAXK];

/*struct BIT {
    int vv[MAXK];
    inline int lowbit( int i ) {
        return i & ( -i );
    }
    int ask( int i ) {
        int ret = 0;
        for( ; i; i -= lowbit( i ) )    ret += vv[i];
        return ret;
    }
    void add( int i, int v ) {
        for( ; i <= K; i += lowbit( i ) ) vv[i] += v;
    }
} T;*/
struct treearray
{
    int tre[MAXK],kk;
    int lwbt(int x){return x&(-x);}
    int ask(int i){int ans=0; for(;i;i-=lwbt(i))ans+=tre[i];return ans;}
    void add(int i,int K){for(;i<=kk;i+=lwbt(i))tre[i]+=K;}
}T;
//code====================================
bool cmp_x( node aa, node bb )
{
    if( aa.x != bb.x )  return aa.x < bb.x;
    if( aa.y != bb.y )  return aa.y < bb.y;
    return aa.z < bb.z;
}
bool cmp_y( node aa, node bb )
{
    if(aa.y==bb.y)
        return aa.z<bb.z;
    return aa.y<bb.y;
}
//cdq=======================================
void cdq(int l,int r) {
    if(l==r)    return;
    int mid=(l+r)>>1;
    cdq(l,mid);cdq(mid+1,r);
    sort(a+l,a+mid+1,cmp_y);
    sort(a+mid+1,a+r+1,cmp_y);
    int i=mid+1,j=l;
    for(;i<=r;++i) {
        while(a[j].y<=a[i].y &&j<=mid)
            T.add(a[j].z,a[j].w),j++;
        a[i].ans+=T.ask(a[i].z);
    }
    for(i=l;i<j;++i)
        T.add(a[i].z,-a[i].w);
}
//main======================================
int main()
{
    N = rd(), K = rd();
    T.kk=K;
    //printf("%d %d\n",N,K);
    for( int i = 1; i <= N; ++i )
        b[i].x = rd(), b[i].y = rd(), b[i].z = rd();
    sort( b + 1, b + N + 1, cmp_x );
    int c=0;
    for( int i = 1; i <= N; ++i ) {
        ++c;
        if( b[i].x != b[i + 1].x || b[i].y != b[i + 1].y || b[i].z != b[i + 1].z )
            a[++cnt] = b[i], a[cnt].w = c, c = 0;
    }
    //for(int i=1;i<=cnt;++i)
    //    printf("(%d,%d,%d) w=%d\n",a[i].x,a[i].y,a[i].z,a[i].w);;
    //printf("cnt=%d\n",cnt);
    cdq(1,cnt);
    for(int i=1;i<=cnt;++i)
        ans[a[i].ans+a[i].w-1]+=a[i].w;
    for(int i=0;i<N;++i)
        printf("%d\n",ans[i]);
    return 0;
}