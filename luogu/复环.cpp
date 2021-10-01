/**
Bellman
Luogu P3385
复环
*/
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
#include <map>
using namespace std;
int T;
int N,M;
struct edge
{
    int ed;
    int vv;
    int next;
} E[600010];
int Ecnt;
int minDis[200010];
int edgeIndex[200010];
bool inStack[200010];
#define Set0(x) memset(x,0,sizeof(x))
#define SetMax(x) memset(x,0x3f,sizeof(x))
//!code
void add(int s,int e,int v)
{
    E[++Ecnt].ed=e;
    E[Ecnt].vv=v;
    E[Ecnt].next=edgeIndex[s];
    edgeIndex[s]=Ecnt;
}
void init()
{
    Set0(E);
    Set0(edgeIndex);
    SetMax(minDis);
    Ecnt=0;
    scanf("%d%d",&N,&M);
    for(int i=1; i<=M; ++i)
    {
        int a,b,w;
        scanf("%d%d%d",&a,&b,&w);
        if(w<0)
        {
            add(a,b,w);
        }
        else
        {
            add(a,b,w);
            add(b,a,w);
        }
    }
}
void SPFA(int S=1)
{
    inStack[S]=true;
    int t=edgeIndex[S];
    cout<<S<<endl;
    while(t!=0)
    {
        if(E[t].ed+minDis[S]<minDis[E[t].ed])
        {
            minDis[E[t].ed]=E[t].ed+minDis[S];
            if(!inStack[E[t].ed])
            {
                SPFA(E[t].ed);
            }
            else
            {
                puts("YE5");
                exit(0);
            }
        }
        t=E[t].next;
    }
    inStack[S]=false;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        init();

        for(int i=1; i<=N; ++i)
        {
            int n=edgeIndex[i];
            while(n!=0)
            {
                cout<<i<<" > "<<E[n].ed<<" = "<<E[n].vv<<endl;
                n=E[n].next;
            }
        }

        for(int i=1; i<=N; ++i)
        {
            Set0(inStack);
            SPFA(i);
        }

    puts("N0");
    }

    return 0;
}
