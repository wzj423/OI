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
struct seg{int b,e;}S[11000];
struct sc{int num,vv;}C[11000];
int N,M,ans;
// code
bool cmp1(sc a,sc b){return a.vv<b.vv;}
bool cmp2(seg a,seg b){return a.e<b.e;}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i)
        scanf("%d%d",&S[i].b,&S[i].e);
    for(int i=1;i<=M;++i)
        scanf("%d%d",&C[i].vv,&C[i].num);
    sort(S+1,S+N+1,cmp2);
    sort(C+1,C+M+1,cmp1);
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
        {
            if(C[j].num&&C[j].vv>=S[i].b&&C[j].vv<=S[i].e)
                {
                    ++ans,--C[j].num;
                    break;
                }
        }
    printf("%d\n",ans);
    return 0;
}