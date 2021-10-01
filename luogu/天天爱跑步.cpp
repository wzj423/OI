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
struct edge {
    int next,ed;
} E[1000010];
int head[300010],Ecnt;

int fa[300010][22];
int depth[300010];
int ww[300010];

// code
inline void addEdge(int st,int ed)
{
    E[++Ecnt].ed=ed;
    E[Ecnt].next=head[st];
    head[st]=Ecnt;
}
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<N;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addEdge(x,y);
        addEdge(y,x);        
    }
    for(int i=1;i<=N;++i)
        scanf("%d",ww+i);
    
    return 0;
}