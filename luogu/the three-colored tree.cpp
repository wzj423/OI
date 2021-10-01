#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
 
#include <algorithm>
#include <queue>
#include <stack>
 
#include <cmath>
#include <cstring>
#include <string>
#include <cctype>
using namespace std;
const int MAXN=500000+100;
struct node
{
    int L,R;
}T[MAXN*2];
int Tcnt=1;
int f[MAXN*2][3];
int g[MAXN*2][3];
// codecvt
void build_tree(int i)
{
    char c[2];
    scanf("%1s",c);
    if(c[0]=='0')  return;
    T[i].L=++Tcnt;
    build_tree(T[i].L);
    if(c[0]=='2')
    {
        T[i].R=++Tcnt;
        build_tree(T[i].R);
    }
}
void dfs(int st)
{
    if(st==0)   return;
    dfs(T[st].L);
    dfs(T[st].R);
    int l=T[st].L,r=T[st].R;
    f[st][0]=max((f[l][1]+f[r][2]+1),(f[l][2]+f[r][1]+1));
    f[st][1]=max((f[l][0]+f[r][2]),(f[l][2]+f[r][0]));
    f[st][2]=max((f[l][0]+f[r][1]),(f[r][0]+f[l][1]));
}
void dfs2(int st)
{
    if(st==0)   return;
    dfs2(T[st].L);
    dfs2(T[st].R);
    int l=T[st].L,r=T[st].R;
    g[st][0]=min((g[l][1]+g[r][2]+1),(g[l][2]+g[r][1]+1));
    g[st][1]=min((g[l][0]+g[r][2]),(g[l][2]+g[r][0]));
    g[st][2]=min((g[l][0]+g[r][1]),(g[r][0]+g[l][1]));
}
int main()
{
    build_tree(1);
    dfs(1);
    dfs2(1);
    printf("%d ",max(max(f[1][0],f[1][1]),f[1][2]));
    printf("%d\n",min(min(g[1][0],g[1][1]),g[1][2]));
    return 0;
}