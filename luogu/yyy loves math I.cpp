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
long double t,ans=0;
int main()
{
    while(scanf("%LF",&t)!=EOF)
    {
        ans=ans+t*1000000;
    }
    printf("%0.5Lf",ans/1000000);
    return 0;
}