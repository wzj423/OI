#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include<string>
using namespace std;
const int maxn=10005,maxl=1000005;
int n,r,a[maxn],top,ans[maxl],vis[maxl];
int check(int x) 
{
    if (ans[x]!=0) return ans[x];
    int sum=0;
    int y=x;
    while (y<=r) {
        sum+=vis[y];
        y+=x;
    }
    ans[x]=sum;
    return sum;
}
int main() 
{
    scanf("%d",&n);
    for (int i=1; i<=n; i++) 
    {
        scanf("%d",&a[i]);
        vis[a[i]]++;
        if (a[i]>r) r=a[i];
    }
    int top=r;
    for (int i=1; i<=n; i++) 
    {
        while (top>1&&check(top)<i) top--;
        printf("%d\n",top);
    }
    return 0;
}