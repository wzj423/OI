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
typedef long long LL;
const LL INF=0x3f3f3f3f;
int N,M,K;
int a[410][410];
LL pre[410][410];
LL B[1000010];
LL ans;
// code
inline LL qsum(int x1,int y1,int x2,int y2)
{
    return (pre[x2][y2]-pre[x2][y1-1]-pre[x1-1][y2]+pre[x1-1][y1-1])%K;
}
int main()
{
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
        {
            scanf("%d",&a[i][j]);
            pre[i][j]=pre[i][j-1]+a[i][j];
        }
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
            pre[i][j]+=pre[i-1][j];
    /*while(true)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        cout<<qsum(a,b,c,d)<<endl;
    }*/
    for(int i=1;i<=N;++i)
    {
        for(int j=i;j<=N;++j)
        {
            //printf("check in [%d,%d]\n",i,j);
            //memset(B,0,sizeof B);
            for(int k=1;k<=M;++k)
            {

                LL t=qsum(i,1,j,k);
                //printf("k=%d sum=%lld pre=%d\n",k,t,B[t]);
                if(t==0)    ++ans;
                ans+=B[t];
                //printf("\tans = %lld now\n",ans);
                ++B[t];
            }
            for(int k=1;k<=M;++k)
            {
                LL t=qsum(i,1,j,k);
                B[t]=0;                
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}