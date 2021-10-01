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
int N,T;
int a[10010];
double up,down;
// code

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        up=down=0;
        for(int i=1;i<=N;++i)
        {
            scanf("%d",a+i); 
            up+=a[i]+0.5;
            if(a[i]>=1)
                down+=a[i]-0.5;           
        }
        if(up>100&&down<=100)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}