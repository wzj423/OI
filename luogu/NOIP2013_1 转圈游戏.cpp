/**
NOIP2013 TG T1
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <queue>
#include <stack>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

using namespace std;
int N,M,K,X;
int ans;
//! code
int qm(int index,int modNum)
{
    int t=1;
    if(index==1)
        return 10%modNum;
    if(index&1)
        t=10;
    int low=qm(index/2,modNum)%modNum;
    return ((low%modNum)*(low%modNum)%modNum*t)%modNum;
}
int main()
{
    scanf("%d%d%d%d",&N,&M,&K,&X);
    /**
    求10^k*m%n+x
    */
    int t=qm(K,N);
    ans=(t*M%N+X)%N;
    cout<<ans<<endl;
    return 0;
}
