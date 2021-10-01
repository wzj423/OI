
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool biao[65537];
long long a[100001],b[100001];
inline void inl(long long &p,char c=getchar())//long long读入优化
{
    while(c<'0' or c>'9')
        c=getchar();
    p=0;
    while(c>='0' and c<='9')
        p=p*10+c-'0',c=getchar();
}
inline void in(int &p,char c=getchar())//int读入优化
{
    while(c<'0' or c>'9')
        c=getchar();
    p=0;
    while(c>='0' and c<='9')
        p=p*10+c-'0',c=getchar();
}
int main()
{
    int t;
    in(t);
    while(t--)
    {
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(biao,0,sizeof(biao));
        int n;
        in(n);
        inl(a[1]);
        b[1]=a[1];
        biao[a[1]]=1;
        for(int i=2;i<=n;i++)
        {
            inl(a[i]);
            for(int l=a[i],r=a[i]+1;;)//l,r中要有一个从a[i]开始找（说不定a[i]不是第一次出现了）
            {
                if(biao[l])
                {
                    b[i]=a[i]-l;
                    break;
                }
                if(biao[r])
                {
                    b[i]=r-a[i];
                    break;
                }
                if(l>0)//防止访问非法内存
                    l--;
                if(r<65536)
                    r++;
            }
            biao[a[i]]=1;
        }
        for(int i=2;i<=n;i++)
            b[i]+=b[i-1];
        printf("%lld\n",b[n]);
    }
    return 0;
}
