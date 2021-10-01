#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
int N,a[25];
int main() {
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
        scanf("%d",&a[i]);
    for(int i=1; i<=N; ++i)
        if(!a[i]) 
        {
            if(i%2==0)
            {
                puts("YES");
                return 0;
            }
            break;
        }
    for(int i=N; i>=1; --i)
        if(!a[i]) 
        {
            if((N-i+1)%2==0)
            {
                puts("YES");
                return 0;
            }
            break;
        }
    puts("NO");
    return 0;
}