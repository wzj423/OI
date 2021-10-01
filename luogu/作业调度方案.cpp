/**
作业调度方案
Luogu P1065
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
int N,M;
int curGongxu[30];
int sequence[500];
int machineId[500];
int costTime[500];
// code
void init()
{
    scanf("%d%d",&M,&N);
    for(int i=1;i<=M*N;++i)
    {
        scanf("%d",&sequence[i]);
    }
    for(int i=1;i<=N;++i)
    {
        curGongxu[i]=1;
    }
    for(int i=1;i<=M*N;++i)
    {
        scanf("%d",&machineId[i]);
    }
    for(int i=1;i<=M*N;++i)
    {
        scanf("%d",&costTime[i]);
    }
}
int main()
{

    return 0;
}
