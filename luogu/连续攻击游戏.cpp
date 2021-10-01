/**
连续攻击游戏
SCOI 2010
Luogu P1640
二分图
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
struct edge
{
    int st;
    int ed;
}E[6000010];
int Ecnt;
int N;
//! code
bool cmp(edge a,edge b)
{
    return a.st<b.st;
}
void addEdge(int x,int y)
{
    E[++Ecnt].st=x;
    E[Ecnt].ed=y;
}
void init()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        addEdge(i,a);
    }
    sort(E+1,E+Ecnt+1,cmp);
}
int main()
{
    init();
    return 0;
}
