#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <utility>
#include <queue>
#include <stack>

using namespace std;
typedef long long LL;
const LL INF=0x3f3f3f3f;
int T,N,a[1000100],f[1000100];

// code
inline int gi()
{
    char ch=getchar();int x=0;
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch))  x=x*10+ch-'0',ch=getchar();
    return x;
}
int main()
{
    T=gi();
    while(T--)
    {
        N=gi();
        for(int i=1;i<=N;++i)
            a[i]=gi();
        for(int i=1;i<=N;++i)
        {
            f[a[i]]=f[a[i]-1]+1;
            if(a[i]==N)  break;
        }
        printf("%d\n",N-f[N]);
    }
    return 0;
}