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
int N,M,T;
bool b;
// code

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        b=true;
        scanf("%d%d",&N,&M);
        while(true)
        {
            if(N<M)
                swap(N,M);
            if(N%M==0||N>2*M)
                break;
            N-=M;
            b=!b;
        }
        if(b) puts("Stan wins");
        else puts("Ollie wins");
    }

    return 0;
}
