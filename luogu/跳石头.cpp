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
int L,N,M;
int a[50010];
int up=0x3f3f3f3f,low=1;
// code
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int judge(int dis)
{
    int cnt=1;
    int from=1;
    for(int i=2; i<=N; ++i)
    {
        if(a[i]-a[from]>=dis)
        {
            ++cnt;
            from=i;
        }
    }
    return N-cnt;
}
void init()
{
    L=read(),N=read(),M=read();
    N+=2;
    a[N]=L;
    for(int i=2; i<=N-1; ++i)
        a[i]=read();
}
void work()
{
    while(low<=up)//二分最短跳越距离(不降)
    {
        int mid=low+(up-low)/2;
        if(judge(mid)<=M)
        {
            low=mid+1;
        }
        else up=mid-1;
    }
    printf("%d\n",low-1);
}
int main()
{
    init();
    work();
    //system("pause");
    return 0;
}