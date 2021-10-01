/**
NOIP2013 TG T1
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <queue>
#include <stack>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

using namespace std;
int N;
int a[100010];
int acnt;
int ans;
//! code
void init()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
    {
        int x;
        scanf("%d",&x);
        if(x!=a[acnt])
            a[++acnt]=x;
    }
        //scanf("%d",&a[i]);
}
void work()
{
    for(int i=2;i<N;++i)
        if((a[i-1]<a[i]&&a[i+1]<a[i])||(a[i-1]>a[i]&&a[i+1]>a[i]))
           ans++;
    ans+=2;
}
int main()
{
    init();
    work();
    printf("%d",ans);
    return 0;
}
