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
int N,a[110000],tot;
int f[110000];
// code

int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
    {
        scanf("%d",&a[i]);
        tot+=a[i];
    }
    //printf("%d\n",tot);
    tot>>=1;
    for(int i=1;i<=N;++i)
        for(int j=tot;j>=a[i];--j)
            f[j]=max(f[j],f[j-a[i]]+a[i]);
    printf("%d ",f[tot]);
    return 0;
}