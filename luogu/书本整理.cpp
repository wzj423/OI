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
int dp[110][110];
int N,K;
struct book
{
    int Hei;
    int Wei;
}W[110];
const int INF=0x3f3f3f3f;
// code
bool cmp(book a,book b)
{
    return a.Hei<b.Hei;
}
void init()
{
    int tt;
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;++i)
    {
        scanf("%d%d",&W[i].Hei,&W[i].Wei);
    }
    sort(W+1,W+N+1,cmp);
    //for(int i=1;i<=N;++i)
}
void work()
{
    for(int i=1;i<=N;++i)
    {
        for(int j=2;j<=N-K&&j<=i;++j)
        {
            dp[i][j]=INF;
            for(int k=j-1;k<=i-1;++k)
            {
                dp[i][j]=min(dp[i][j],dp[k][j-1]+abs(W[i].Wei-W[k].Wei));
            }
        }
    }
    int ans=INF;
    for(int i=N-K;i<=N;++i)
    {
        ans=min(ans,dp[i][N-K]);
    }
    printf("%d",ans);
}
int main ()
{
    init();
    work();
    return 0;
}
