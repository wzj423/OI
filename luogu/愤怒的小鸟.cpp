/*
状压dp
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include<string>

#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
using namespace std;

int T,N,M;
double pig[30][2];
int line[900];// status
int lineCnt;

int dp[(1<<20)];
// code
inline bool equal(double a,double b)
{
    double x=a-b;
    if(x<0)x=-x;
    return x<1e-6;
}
void init()
{
    memset(pig,0,sizeof pig);
    memset(line,0,sizeof line);
    memset(dp,0x3f,sizeof dp);
    dp[0]=0;
    lineCnt=0;
    scanf("%d%d",&N,&M);
    for(int i=0;i<N;++i)
        scanf("%lf%lf",&pig[i][0],&pig[i][1]);
    for(int i=0;i<N;++i)
    {
        for(int j=i+1;j<N;++j)
        {
            double x1=pig[i][0],y1=pig[i][1],x2=pig[j][0],y2=pig[j][1];
            double a=0,b=0;
            if(equal(x1,x2)||(y2*x1-y1*x2)/(x1*x2*(x2-x1))>-1e-8)
                continue;                
            a=(y2*x1-y1*x2)/(x1*x2*(x2-x1));
            b=(y1*x2*x2-y2*x1*x1)/(x1*x2*x2-x2*x1*x1);
            line[++lineCnt]=((1<<i)|(1<<j));
            //查找其他点
            for(int k=0;k<N;++k)
            {
                double x3=pig[k][0],y3=pig[k][1];
                if(equal(a*x3*x3+b*x3,y3))
                     line[lineCnt]|=(1<<k);         
            }
        }
        line[++lineCnt]=(1<<i);        
    }
    sort(line+1,line+lineCnt+1);
    lineCnt=unique(line+1,line+lineCnt+1)-line-1;
}

void work()
{
    for(int i=0;i<(1<<(N));++i)
        for(int j=1;j<=lineCnt;++j)
            if(dp[line[j]|i]>dp[i]+1)
                dp[line[j]|i]=dp[i]+1;
    printf("%d\n",dp[(1<<(N))-1]);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        init();
        work();
    }
    return 0;
}
