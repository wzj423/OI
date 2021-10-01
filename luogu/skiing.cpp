#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <cctype>
#include <string>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
int ski[120][120];
int help[120][120];
int ans;
int R,C;
int step[10][2]={{0,0},{0,1},{0,-1},{1,0},{-1,0}};
#define isOK(a1,b1) (a1>=1&&a1<=R&&b1>=1&&b1<=C&&ski[a1][b1]<ski[a][b])
int dfs(int a,int b)
{
    if(help[a][b]!=0)
        return help[a][b];
    int res=0;
    for(int i=1;i<=4;i++)
    {
        if(isOK(a+step[i][0],b+step[i][1]))
            res=max(res,dfs(a+step[i][0],b+step[i][1]));
    }
    help[a][b]=res+1;
    return res+1;
}
int main()
{
    cin>>R>>C;
    for(int i=1;i<=R;i++)
        for(int j=1;j<=C;j++)
            cin>>ski[i][j];
    for(int i=1;i<=R;i++)
        for(int j=1;j<=C;j++)
            ans=max(ans,dfs(i,j));
    cout<<ans<<endl;
    while (0)
    for(int i=1;i<=R;i++)
        for(int j=1;j<=C;j++)
            cout<<help[i][j]<<(j==C?'\n':' ');
    return 0;
}
