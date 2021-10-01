
#include<cstdio>
typedef long long ll;
const int maxn=100005;
ll d[maxn],id[maxn],s[maxn],k;
int n,m,c,x,y;
void add(ll*b,int p,ll v){for(;p<=n;p+=p&-p)b[p]+=v;}
ll ask(ll*b,int p)
{
    ll a=0;
    for(;p;p-=p&-p)a+=b[p];
    return a;
}
ll ask(int p){return s[p]+(p+1)*ask(d,p)-ask(id,p);}
void add(int x,int y,ll v)
{
    add(d,x,v);add(d,y+1,-v);
    add(id,x,v*x);add(id,y+1,-v*(y+1));
}
int main()
{
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=n;++i)scanf("%lld",s+i),s[i]+=s[i-1];
    while(m--)
    {
        scanf("%d%d%d",&c,&x,&y);
        if(c==1)scanf("%lld",&k),add(x,y,k);
        else printf("%lld\n",ask(y)-ask(x-1));
    }
    return 0;
}
