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
int f[1100],key[1100];
int N,M,T;
bool flag;
// code
int get_dad(int x)
{
    if(!f[x])   return x;
    int fa=f[x];
    f[x]=get_dad(f[x]);
    key[x]+=key[fa];
    return f[x];
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&N,&M);
        memset(f,0,sizeof f),memset(key,0,sizeof key);
        flag=true;
        for(int i=1;i<=M;++i)
        {
            int x,y,z,fx,fy;
            scanf("%d%d%d",&x,&y,&z);
            ++y;

            fx=get_dad(x),fy=get_dad(y);
            if(fx!=fy)
            {
                f[fx]=fy;
                key[fx]=key[y]-key[x]-z;
            }
            else
                flag&=(key[x]+z==key[y]);
        }
        if(flag)    puts("true");
        else        puts("false");
    }
    return 0;
}