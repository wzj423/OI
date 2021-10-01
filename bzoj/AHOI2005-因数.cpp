/**
AC
*/
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

int N;
int ans;
// code

int main()
{
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
        for(int j=1; i*j<=N; ++j)
            ++ans;
    printf("%d\n",ans);
    //system("pause");
    return 0;
}