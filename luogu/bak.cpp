#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <map>
#include <set>
//#include <multimap>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
const int MAXN=100010;
const int INF=0x3f3f3f3f;
typedef  long long  LL;

int H[MAXN];
int X[MAXN];
int N,M;

map<int,int> hei;
typedef map<int,int>::iterator Iter;
typedef map<int,int>::reverse_iterator RIter;
LL a[MAXN];//目的地
LL b[MAXN];//
LL F[MAXN][23];//两天一次,2^j次 目的地
LL adis[MAXN][23];//距离
LL bdis[MAXN][23];
// code
void init()
{
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
        scanf("%d",&H[i]);
    scanf("%d",&X[0]);
    scanf("%d",&M);
    int s,x;
    for(int i=1; i<=M; ++i)
    {
        scanf("%d%d",&s,&x);
        X[s]=x;
    }
}
bool cmp(pair<int,int> a,pair<int,int> b)
{
    if(abs(a.first)!=abs(b.first))
        return abs(a.first)<abs(b.first);//差小在前
    return a.first<b.first;//负号在前
}
void display(pair<int,int> a)
{
    printf("Met Height %d id %d\n",a.first,a.second);
}
void calc_next()
{
    vector<pair<int,int> > t;
    for(int i=N; i>=1; --i)
    {
        t.clear();
        RIter tmp1;
        Iter tmp2;

        hei[H[i]]=i;
        tmp2=hei.find(H[i]);//tmp2 向后 tmp1向前
        ++tmp2;        
        if(tmp2!=hei.end())
        {
            t.push_back(*tmp2);
            tmp2++;
            if(tmp2!=hei.end())
                t.push_back(*tmp2);
            --tmp2;
        }
        --tmp2;
        if(tmp2!=hei.begin())
        {
            --tmp2;
            t.push_back(*tmp2);
            if(tmp2!=hei.begin())
            {
                --tmp2;
                t.push_back(*tmp2);
                ++tmp2;
            }
            ++tmp2;
        }
        //开始排序
        for(int j=0; j<t.size(); ++j)
        {   
            t[j].first-=H[i];
        }

        sort(t.begin(),t.end(),cmp);

        if(t.size()>0)
        {
            b[i]=t[0].second;
            bdis[i][0]=abs(t[0].first);
            if(t.size()>1)
            {
                a[i]=t[1].second;
                adis[i][0]=abs(t[1].first);
            }
        }
    }
}
void calc_double()//倍增
{
    for(int i=1;i<=N;++i)
        F[i][0]=b[a[i]];
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=N;++j)
        {
            if(F[ F[j][i-1] ][i-1])
            {
                F[j][i]=F[ F[j][i-1] ][i-1];  
                adis[j][i]=adis[j][i-1]+adis[ F[j][i-1] ][i-1];
                bdis[j][i]=bdis[j][i-1]+bdis[ F[j][i-1] ][i-1];                              
            }
        }
    }
}
void ask1()
{
    double minNum=double(INF);
    int ret=-1;
    for(int i=1;i<=N;++i)
    {
        //倍增查询
        int cur=i;
        int totA=0,totB=0;
        double curAns=0;
        for(int i=20;i>=0;--i)
        {
            if(F[cur][i]&&adis[cur][i]+bdis[cur][i]+totA+totB<=X[0])
            {
                totA+=adis[cur][i];
                totB+=bdis[cur][i];
                cur=F[cur][i];
            }
        }
        if(a[cur]&&adis[cur][0]+totA+totB<=X[0])
            totA+=adis[cur][0],cur=a[cur];
        if(totB==0) curAns=double(INF);
        else curAns=double(totA)/double(totB);

printf("totA %d  totB %d  rate %lf   start point %d\n",totA,totB,curAns,i);

        if(curAns<minNum)
        {
            minNum=curAns;
            ret=i;
        }
    }
    printf("%d\n",ret);
}
void work()
{
    calc_next();
    calc_double();
    for(int i=1; i<=N; ++i)
    {
         printf("At %d A to %lld B to %lld  dist of A:%lld  B:%lld\n",i,a[i],b[i],adis[i][0],bdis[i][0]);
    }
    puts("\n\n");
    for(int i=1; i<=N; ++i)
    {
         printf("At %d couple to %d\n",i,F[i][0]);
    }
    puts("_____________________________________________");
    printf("%d %d\n",adis[2][0],bdis[2][0]);
    puts("_____________________________________________");


    for(int i=1; i<=N; ++i)
    {
        for(int j=0;j<=2;++j)
            printf("People will come to %lld with a dist of A:%lld  B:%lld(%d,%d)\n",F[i][j],adis[i][j],bdis[i][j],i,j);
    }
    ask1();
}
int main()
{
    init();
    work();
    return 0;
}