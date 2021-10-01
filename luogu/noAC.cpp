/*HDU
2037
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
typedef long long LL;
struct seg{int a,b;}S[110];
int N;
// code
bool cmp(seg x,seg y)
{
    return x.a<y.a;
}
int main()
{
    while(scanf("%d",&N)!=EOF)
    {
        if(N==0)    break;
        int ans=0,cur=0;
        for(int i=1;i<=N;++i)
            scanf("%d%d",&S[i].a,&S[i].b);
        sort(S+1,S+N+1,cmp);
        for(int i=1;i<=N;++i)
        {
            if(S[i].b<S[cur].b) cur=i;
            else if(S[i].a>=S[cur].b)   cur=i,++ans;
        }
        printf("%d\n",ans);
    }
    return 0;
}