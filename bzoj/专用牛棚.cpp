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
int delta[1000010];
int N;
// code

int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        delta[x]++;
        delta[y+1]--;
    }
    int ans=0,curNum=0;
    for(int i=1;i<=1000001;++i)
    {
        curNum+=delta[i];
        ans=max(ans,curNum);
    }
    printf("%d\n",ans);
    system("pause");
    return 0;
}