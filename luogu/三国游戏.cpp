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
int N;
int mat[1010][1010];
// code


void init()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
        for(int j=i+1;j<=N;++j)
        {
            scanf("%d",&mat[i][j]);
            mat[j][i]=mat[i][j];
        }
}


void work()
{

    int ans=0,mx1=0,mx2=0,t;
    for(int i=1;i<=N;++i)
    {
        mx1=mx2=0;
        for(int j=1;j<=N;++j)
        {
            t=mat[i][j];
            if(t>=mx1)
                mx2=mx1,mx1=t;
            else if(t>=mx2)
                mx2=t;
        }        
        //printf("MX2 is %d\n",mx2);
        ans=max(ans,mx2);
    }
    printf("1\n%d\n",ans);
}
int main()
{
    freopen("sanguo.in","r+",stdin);
    freopen("sanguo.out","w+",stdout);
    init();
    work();
    return 0;
}