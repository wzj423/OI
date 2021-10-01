/**

模板 二分图最大匹配
Luogu P3386
邻接矩阵
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
int N,M;
int E;
int mat[1010][1010];
int link[1010];
int used[1010];
int ans;
/// code
void init()
{
    scanf("%d%d%d",&N,&M,&E);
    for(int i=1;i<=E;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(y<=M)
            mat[x][y]=true;
    }
}
bool dfs(int st)
{
    for(int i=1;i<=M;++i)
    {
        if(mat[st][i]==true&&used[i]==false)
        {
            used[i]=true;
            if(link[i]==0||dfs(link[i])==true)
            {
                link[i]=st;
                return true;
            }
        }
    }
    return false;
}
void work()
{
    for(int i=1;i<=N;++i)
    {
        memset(used,0,sizeof(used));
        if(dfs(i))
            ++ans;
    }
}
int  main()
{
    init();
    work();
    printf("%d",ans);
    return 0;
}
