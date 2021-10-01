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
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
    while(true)
    {
        b=true;
        scanf("%d%d",&N,&M);
        if(N+M==0) return 0;
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

