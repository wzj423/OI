#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
struct site{int h,v;}S[100010],T[100010];
int a[100010],Tcnt;
int N;
// code
void push(int i)
{
    while(Tcnt&&T[Tcnt].h<=S[i].h)
        a[i]+=T[Tcnt--].v;
    T[++Tcnt]=S[i]; 
}
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
        scanf("%d%d",&S[i].h,&S[i].v);
    for(int i=1;i<=N;++i)
        push(i);
    Tcnt=0;
    for(int i=N;i>=1;--i)
        push(i);
    for(int i=1;i<=N;++i)
        printf("%d ",a[i]);
    return 0;
}