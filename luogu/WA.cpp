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

// code
int pow1(int a,int x)
{
    int ret=1;
    if(x==0)    return 1;
    for(int i=1;i<=x;++i)
    {
        ret*=a;
    }
    return ret;
}
int main()
{
    int ans=0;
    for(int i=1; i<=8; ++i)
    {
        int x,t=1;
        cin>>x;
        for(int j=0; j<=3; ++j)
        {
            ans+=pow(x,j);
        }
    }
    printf("%d\n",ans);
    return 0;
}