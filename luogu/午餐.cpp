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
int N;
struct pe
{
    int x,y;
} P[1010];
int pre[1010];
int f[210][210*210];
// code
bool cmp(pe a,pe b)
{
    return a.y>b.y;
}
int main()
{
    scanf("%d",&N);
    for(int i=1; i<=N; ++i)
        scanf("%d%d",&P[i].x,&P[i].y);
    sort(P+1,P+N+1,cmp);
    for(int i=1; i<=N; ++i)
        pre[i]=pre[i-1]+P[i].x;
    memset(f,0x3f,sizeof f);
    f[0][0]=0;
    for(int i=1; i<=N; ++i)
        for(int j=0; j<=pre[i-1]; ++j)
        {
            f[i][j]=min(f[i][j],max(f[i-1][j],pre[i-1]-j+P[i].x+P[i].y));
            f[i][j+P[i].x]=min(f[i][j+P[i].x],max(f[i-1][j],j+P[i].x+P[i].y));
        }

    int ans=0x3f3f3f3f;
    for(int i=0; i<=pre[N]; ++i)
        ans=min(ans,f[N][i]);
    printf("%d\n",ans);
    return 0;
}