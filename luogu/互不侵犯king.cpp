#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>
#include <string>

#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
typedef long long LL;
int N,K;
LL f[11][90][1<<11];
int num1[1<<11];
// code
void calc_num1()
{
    for(int i=1;i<(1<<N);++i)
    {
        num1[i]=num1[i>>1]+(i&1);
    }
}
int main()
{
    scanf("%d%d",&N,&K);
    calc_num1();
    //printf("%d\n",num1[2]);
    for(int j=0;j<=K;++j)
        for(int k=0;k<(1<<N);++k)
        {
            if((k&(k>>1))!=0)   continue;
            if(num1[k]!=j)   continue;
            f[1][j][k]=1;
        }
    for(int i=2;i<=N;++i)
        for(int j=0;j<=K;++j)
            for(int k=0;k<(1<<N);++k)
            {
                if((k&(k>>1))!=0)   continue;
                if(num1[k]>j)   continue;
                //printf("f[%d][%d][%d]=%lld\n",i,j,k,f[i][j][k]);
                for(int l=0;l<(1<<N);++l)
                {
                    if( (l&(l>>1)) != 0 )   continue;
                    if( (l&k)   != 0 ) continue;
                    if( ((l>>1)&k) !=0 ) continue;
                    if( ((l<<1)&k) !=0 ) continue;
                    if(num1[l] > j-num1[k]) continue;
                    f[i][j][k]+=f[i-1][j-num1[k]][l];
                    //printf("\t+f[%d][%d][%d]=%lld\n",i-1,j-num1[k],l,f[i-1][j-num1[k]][l]);
                }
                
            }
    LL ans=0;
    for(int i=0;i<(1<<N);++i)
            ans+=f[N][K][i];
    printf("%lld\n",ans);
    return 0;
}