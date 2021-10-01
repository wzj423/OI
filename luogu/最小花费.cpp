/**
最小花费
Luogu P1576
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <cmath>
#include <cctype>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
const double INF=1.1e305;
int N,M;
int S,T;
double m[2010][2010];
double minCost[2010];
bool used[2010];
//!code
void init()
{
    memset(m,0x3f,sizeof(m));
    /*for(int i=1;i<=2000;++i)
    {
        minCost[i]=INF;
    }
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            m[i][j]=INF;*/
    memset(minCost,0x7f,sizeof(minCost));
    memset(m,0x7f,sizeof(m));
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;++i)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        m[a][b]=m[b][a]=(100.0/(100.0-c));
    }
    /*for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            cout<<m[i][j]<<(j==N?'\n':' ');
            */
    scanf("%d%d",&T,&S);
}
void dijkstra(int s)
{
    int next;
    double minNext;
    used[s]=true;
    minCost[s]=1;
    for(int i=1;i<N;++i)
    {
        minNext=INF;
        for(int j=1;j<=N;++j)
        {
            if(used[j]==false&&minCost[s]*m[s][j]<minCost[j])
            {
                minCost[j]=minCost[s]*m[s][j];
            }
        }
        for(int j=1;j<=N;++j)
        {
            if(used[j]==false&&minCost[j]<minNext)
            {
                minNext=minCost[j];
                next=j;
            }
        }
        s=next;
        used[next]=true;
        /*cout<<"Next:"<<next<<endl;
        for(int i=1;i<=N;++i)
        {
            cout<<minCost[i]<<" ";
        }
        cout<<endl;*/
    }
}
int main()
{
    init();
    //cout<<minCost[1];
    dijkstra(S);
    minCost[T]*=100;
    printf("%.8lf\n",minCost[T]);
    //cout<<setprecision(11)<<minCost[T]*100<<endl;
    return 0;
}
