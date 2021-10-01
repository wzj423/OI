#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cctype>
#include <cmath>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
const int INF=0x3f3f3f3f;
const int MAXN=1e5+10;
long double ans;
char tt[30];
// code

int main()
{
    for(int i=0;i<15;++i)   scanf("%c",tt+i);
    tt[15]='\0';
    sscanf(tt,"%Lf",&ans);
    //puts(tt);
    //printf("%Lf\n",ans);
    printf("%.8Lf\n",ans/23);
    return 0;
}