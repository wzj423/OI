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
int N,M;
int a[1001000];
struct book
{
    int B,E;
    int num;
} b[1001000];
int c[1001000];//差分数组
int t[1001000];//工作数组
#define DBG printf
// code

void init()
{
    scanf("%d%d",&N,&M);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d",&a[i]);
        c[i]=a[i]-a[i-1];
    }
    for(int i=1; i<=M; ++i)
        scanf("%d%d%d",&b[i].num,&b[i].B,&b[i].E);
    //for(int i=1; i<=N; ++i)
    //    printf("%d ",c[i]);
    //puts("");
}
bool judge(int d)
{
   // DBG("\njudge in %d\n",d);
    //for(int i=1; i<=N; ++i)
    //    t[i]=c[i];
    memcpy(t+1,c+1,sizeof(int)*N);
    //for(int i=1; i<=N; ++i)
    //    printf("%d ",t[i]);
    for(int i=1; i<=d; ++i)
    {
        int B=b[i].B,E=b[i].E,Num=b[i].num;
        t[B]-=Num;
        t[E+1]+=Num;
   //     for(int i=1; i<=N; ++i)
   //         printf("%d ",t[i]);
    //    puts("");
    }
    for(int i=1; i<=N; ++i)
    {
        t[i]+=t[i-1];
        if(t[i]<0)
        {
   //         puts("\nreturn false");
            return false;
        }
    }
    //puts("");
    //for(int i=1; i<=N; ++i)
    //    printf("%d ",t[i]);
    //puts("\nreturn true");
    return true;
}
void work()
{
    int L=1,R=M;
    if(judge(M))
    {
        puts("0");
        exit(0);
    }
    while(L<=R)
    {
        int mid=(L+R)/2;
        if(judge(mid)) L=mid+1;
        else R=mid-1;
    }
    printf("-1\n%d",L);
}
int main()
{
    init();
    work();
    //system("pause");
    return 0;
}